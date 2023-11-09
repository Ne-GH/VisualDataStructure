/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/22 17:28
*******************************************************************************/
//

#ifndef VISUAL_SORT_HPP
#define VISUAL_SORT_HPP

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

struct SortWindow {

    friend class VisualSort;
    QWidget *window = nullptr;
    QGridLayout *layout = nullptr;

    QBarSet *set = nullptr;
    QBarSeries *series = nullptr;
    QChart *chart = nullptr;
    QBarCategoryAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;
    QChartView *chart_view = nullptr;

    std::vector<int> random_arr;

    int speed = 0;
    bool start = false;
    bool pause = false;
    bool stop = false;
    int sleep_time = 20;

    SortWindow() {
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
        std::default_random_engine rand_engine{};
        for (auto &p : random_arr) {
            p = rand_engine() % 100;
        }

        for (int i = 0;i < random_arr.size(); ++i) {
            categories << std::to_string(i).c_str();
        }

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
        slider->setValue(50);
        auto start_but = new QPushButton("开始");
        auto pause_but = new QPushButton("暂停");
        auto stop_but = new QPushButton("停止");

        layout->addWidget(start_but, 10, 1, 1, 1);
        layout->addWidget(pause_but, 10, 3, 1, 1);
        layout->addWidget(stop_but, 10, 5, 1, 1);
        layout->addWidget(slider, 10, 7, 1, 2);



        slider->setTickInterval(true);
        slider->setMaximum(100);
        QObject::connect(slider,&QSlider::valueChanged,[=]{
            speed = slider->value();
        });

        QObject::connect(start_but,&QPushButton::clicked,[=]{
            if (start == false) {
                start = true;
            }
        });
        QObject::connect(pause_but,&QPushButton::clicked,[=]{
            if (pause == false) {
                pause = true;
                pause_but->setText("继续");
            }
            else {
                pause = false;
                pause_but->setText("暂停");
            }
        });
        QObject::connect(stop_but,&QPushButton::clicked,[=]{

        });


    }
};


class VisualSort : public QObject {
Q_OBJECT

signals:
    void UPUI();
private:
    SortWindow *sort_window = nullptr;
public:

    VisualSort(SortWindow *window) {
        sort_window = window;
    }

    void BubbleSort() {
        while (!sort_window->start) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        MSTL::BubbleSort(sort_window->random_arr.begin(),sort_window->random_arr.end(),[&](const auto &val1,const auto &val2) {
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




#endif
