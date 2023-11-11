/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/22 17:28
*******************************************************************************/
//

#pragma once

#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <QThread>
#include <QValueAxis>
#include <QPushButton>
#include <QGridLayout>
#include <QChart>
#include <QThread>
#include <QSplineSeries>
#include <QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QBarCategoryAxis>
#include "Sort.hpp"

struct SortWindow : public QObject{
    Q_OBJECT

public:
    friend class VisualSort;
    QWidget *window = nullptr;
    QGridLayout *layout = nullptr;

    QBarSet *set = nullptr;
    QBarSeries *series = nullptr;
    QChart *chart = nullptr;
    QBarCategoryAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;
    QChartView *chart_view = nullptr;

    QThread *sort_thread = nullptr;
    std::default_random_engine rand_engine;
    std::vector<int> random_arr;

    int speed = 0;
    bool start = false;
    bool pause = false;
    int sleep_time = 20;

    void ReSetRandomNumbers() {
        for (auto &p : random_arr) {
            p = rand_engine() % 100;
        }

        set->remove(0,random_arr.size());
        for (auto num : random_arr) {
            *set << num;
        }
    }

    SortWindow() {
        sort_thread = new QThread();

        layout = new QGridLayout();
        window = new QWidget();
        window->setLayout(layout);

        set = new QBarSet("");
        series = new QBarSeries();
        chart = new QChart();
        axisX = new QBarCategoryAxis();
        axisY = new QValueAxis();
        chart_view = new QChartView(chart);
        QStringList categories;
        series->append(set);
        chart->addSeries(series);
        chart->setTitle("");
//        _chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setAnimationOptions(QChart::NoAnimation);

        random_arr.resize(100);

        for (int i = 0;i < random_arr.size(); ++i) {
            categories << std::to_string(i).c_str();
        }
//        ReSetRandomNumbers();

        axisX->append(categories);
        axisX->setVisible(false);
        axisY->setVisible(false);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        axisY->setRange(0,100);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
        chart->legend()->setVisible(false);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart_view->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(chart_view,0,0,10,10);

        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setValue(40);
        auto start_pause_but = new QPushButton("开始");
        auto stop_but = new QPushButton("停止");

        layout->addWidget(start_pause_but, 10, 1, 1, 1);
        layout->addWidget(stop_but, 10, 5, 1, 1);
        layout->addWidget(slider, 10, 7, 1, 2);



        slider->setTickInterval(true);
        slider->setMaximum(80);
        QObject::connect(slider,&QSlider::valueChanged,[=]{
            speed = slider->value();
        });

        QObject::connect(start_pause_but,&QPushButton::clicked,[=]{
            if (start == false) {

                ReSetRandomNumbers();
                emit Start();
                start = true;
                start_pause_but->setText("暂停");

                random_arr.resize(100);
                std::default_random_engine rand_engine{};
                for (auto &p : random_arr) {
                    p = rand_engine() % 100;
                }
            }
            else {
                if (pause == false) {
                    start_pause_but->setText("继续");
                    pause = true;
                    emit Pause();
                }
                else {
                    start_pause_but->setText("暂停");
                    pause = false;
                    emit Start();

                }
            }
        });

        QObject::connect(stop_but,&QPushButton::clicked,[&]{
            if (start == true) {
                start = false;
                sort_thread->quit();
                emit Stop();
            }
        });


    }

signals:
    void Start();
    void Pause();
    void Stop();

};


class VisualSort : public QObject {
Q_OBJECT

signals:
    void UPUI();
    void Finish();
private:
    SortWindow *sort_window = nullptr;
    bool stop = false;
public:

    VisualSort(SortWindow *window) {
        sort_window = window;
        QObject::connect(sort_window,&SortWindow::Stop,[=]{
            stop = true;
        });
    }

    void BubbleSort() {
        while (!sort_window->start) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        MSTL::BubbleSort(sort_window->random_arr.begin(),sort_window->random_arr.end(),[=](const auto val1,const auto val2) {
            if (stop == true)
                return true;
            while (sort_window->pause) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
            emit UPUI();
            std::this_thread::sleep_for(std::chrono::milliseconds(sort_window->sleep_time * (100 - sort_window->speed) / 100));
            if (val1 < val2)
                return true;
            else
                return false;
        });
        emit UPUI();
        thread()->quit();
        emit Finish();
    }

//    void StdSort() {
//        SORT_FUNC_BASE(std::sort);
//    }
//    void SelectionSort() {
//        SORT_FUNC_BASE(MSTL::SelectionSort);
//    }
//    void InsertionSort() {
//        SORT_FUNC_BASE(MSTL::InsertionSort);
//    }
//    void QuickSort() {
//        SORT_FUNC_BASE(MSTL::QuickSort);
//    }
//    void MergeSort() {
//        SORT_FUNC_BASE(MSTL::MergeSort);
//    }


    void UpUI() {
        auto vec = sort_window->random_arr;
        sort_window->set->remove(0,vec.size());
        for (auto num : vec) {
            *sort_window->set << num;
        }
    }
};