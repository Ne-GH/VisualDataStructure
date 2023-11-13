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

enum class SortType {
    NONE,
    BUBBLE_SORT,
    SELECTION_SORT,
    INSERTION_SORT,
    QUICK_SORT,
    MERGE_SORT,
    STD_SORT
};

class SortThread : public QThread {

    Q_OBJECT

    bool running = false;
    bool pause = false;

    std::vector<unsigned >::iterator begin ,end;
    int sleep_time = 10;
public:
    SortType sort_type = SortType::NONE;
    int speed = 50;
    void SetSortType(SortType type) {
        sort_type = type;
    }
    void SetArr(std::vector<unsigned >::iterator arg_beg ,std::vector<unsigned >::iterator arg_end) {
        begin = arg_beg;
        end = arg_end;
    }
    template <void (*sort_func)(std::vector<unsigned >::iterator,std::vector<unsigned >::iterator,std::function<bool (const unsigned ,const unsigned )>)>
    void Sort() {
        sort_func(begin,end,[=](const auto val1,const auto val2) {
            if (!running) {
                return false;
            }
            while (pause) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            emit UPUI();
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time * (100 - speed) / 100));
            if (val1 < val2)
                return true;
            else
                return false;
        });
        emit UPUI();
        emit Finish();
    }


    void run() override {
        running = true;

        switch (sort_type) {
            case SortType::NONE:
                break;
            case SortType::STD_SORT: {
                Sort<std::sort>();
                break;
            }
            case SortType::BUBBLE_SORT: {
                Sort<MSTL::BubbleSort>();
                break;
            }
            case SortType::SELECTION_SORT: {
                Sort<MSTL::SelectionSort>();
                break;
            }
            case SortType::QUICK_SORT: {
                Sort<MSTL::QuickSort>();
                break;
            }
            case SortType::INSERTION_SORT: {
                Sort<MSTL::InsertionSort>();
                break;
            }
            case SortType::MERGE_SORT: {
                Sort<MSTL::MergeSort>();
                break;
            }
            default:
                break;
        }

    }
    void Start() {
        running = true;
        pause = false;
        start();
    }
    void Pause() {
        pause = true;
    }
    void Continue() {
        pause = false;
    }
    void Stop() {
        running = false;
    }

signals:
    void UPUI();
    void Finish();

};

struct SortWindow : public QObject{
    Q_OBJECT

public:
    QWidget *window = nullptr;
    QGridLayout *layout = nullptr;

    QBarSet *set = nullptr;
    QBarSeries *series = nullptr;
    QChart *chart = nullptr;
    QBarCategoryAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;
    QChartView *chart_view = nullptr;

    QPushButton *start_pause_button = nullptr;
    QPushButton *stop_button = nullptr;
    QSlider *slider = nullptr;

    SortThread *sort_thread = nullptr;
    std::vector<unsigned> random_arr;


    int speed = 0;
    bool start = false;
    bool pause = false;
    bool stop = false;
    int sleep_time = 20;

    void SetSortType(SortType type) {
        sort_thread->Stop();
        sort_thread->SetSortType(type);
    }

    void Start() {
        start = true;
        pause = false;
        start_pause_button->setText("暂停");
        sort_thread->SetArr(random_arr.begin(),random_arr.end());
        sort_thread->Start();
        emit StartSig();
    }

    void Continue() {
        pause = false;
        start_pause_button->setText("暂停");
        emit ContinueSig();
        sort_thread->Continue();
    }
    void Pause() {
        pause = true;
        start_pause_button->setText("继续");
        emit PauseSig();
        sort_thread->Pause();
    }
    void Stop() {
        sort_thread->Stop();
        emit StopSig();
        start = false;
        start_pause_button->setText("开始");
    }

    unsigned GetRandomNumber() {
        static std::random_device dev;
        static std::default_random_engine engine(dev());
        static std::uniform_int_distribution<unsigned > uniform_dist(1,100);
        return uniform_dist(engine);
    }

    void UPUI() {
        set->remove(0,random_arr.size());
        for (auto num : random_arr) {
            *set << num;
        }
    }

    void ReSetRandomNumbers() {
        for (auto &p : random_arr) {
            p = GetRandomNumber();
        }

        UPUI();
    }
    void ConfigUI() {
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

        slider = new QSlider(Qt::Horizontal);
        slider->setValue(40);
        start_pause_button = new QPushButton("开始");
        stop_button = new QPushButton("停止");

        layout->addWidget(start_pause_button, 10, 1, 1, 1);
        layout->addWidget(stop_button, 10, 5, 1, 1);
        layout->addWidget(slider, 10, 7, 1, 2);

        slider->setTickInterval(true);
        slider->setMaximum(80);

    }


    void ConfigThread() {

        if (sort_thread) {
            QObject::disconnect(sort_thread);
            sort_thread->quit();
            delete sort_thread;
            sort_thread = nullptr;
        }
        sort_thread = new SortThread();
        QObject::connect(sort_thread,&SortThread::UPUI,[=]{
            UPUI();
        });
        QObject::connect(sort_thread,&SortThread::Finish,[=]{
            emit FinishSig();
        });
    }
    SortWindow() {
        ConfigUI();
        ConfigThread();


        QObject::connect(slider,&QSlider::valueChanged,[=, this]{
            sort_thread->speed = slider->value();
        });

        QObject::connect(start_pause_button,&QPushButton::clicked,[=,this]{
            if (start == false) {
                Start();
            }
            else {
                if (pause == true)
                    Continue();
                else
                    Pause();
            }
        });

        QObject::connect(stop_button,&QPushButton::clicked,[=,this]{
            Stop();
        });


    }

signals:
    void StartSig();
    void ContinueSig();
    void StopSig();
    void PauseSig();
    void FinishSig();
    void UPUISig();

};