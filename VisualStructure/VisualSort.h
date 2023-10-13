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
//#include "Sort.cppm"
import Sort;

#define CMP \
    [this](auto val1,auto val2) { \
        while(_pause);    \
        emit UPUI();\
        std::this_thread::sleep_for(std::chrono::milliseconds(_sleep_time * (100-_speed) / 100));\
        if (val1 < val2)\
            return true;\
        else\
            return false;\
    }
#define SORT_FUNC_BASE(func) \
    while(!_start);              \
    func(vec.begin(),vec.end(),CMP); \
    emit UPUI();\
    thread()->quit();
class VisualSort : public QObject {
    Q_OBJECT

signals:
    void UPUI();
private:
    std::vector<int >vec;
    int _sleep_time = 20;
    QBarSet *_set = nullptr;
    QBarSeries *_series = nullptr;
    QChart *_chart = nullptr;
    QBarCategoryAxis *_axisX = nullptr;
    QValueAxis *_axisY = nullptr;
    QChartView *_chartView = nullptr;
    // 10 * 50 / 100
    // 10 * 100 / 100;

    bool _start = false;
    bool _pause = false;
    bool _stop = false;
    int _speed = 50;

public:

    VisualSort() {
        GetRandomVector(100);
    }

    void BubbleSort() {
        SORT_FUNC_BASE(MSTL::BubbleSort);
    }
    void StdSort() {
        SORT_FUNC_BASE(std::sort);
    }
    void SelectionSort() {
        SORT_FUNC_BASE(MSTL::SelectionSort);
    }
    void InsertionSort() {
        SORT_FUNC_BASE(MSTL::InsertionSort);
    }
    void QuickSort() {
        SORT_FUNC_BASE(MSTL::QuickSort);
    }
    void MergeSort() {
        SORT_FUNC_BASE(MSTL::MergeSort);
    }
    void GetRandomVector(size_t size) {
        vec.resize(size);
        std::default_random_engine rand_engine;
        for (auto &p : vec) {
            p = rand_engine() % 100;
        }
    }
    auto GetRandomVector() {
        return vec;
    }
    QBarSet *GetBarSet() {
        return _set;
    }




    void CreateSortLayout(QGridLayout *layout) {
        _set = new QBarSet("");
        _series = new QBarSeries();
        _chart = new QChart();
        _axisX = new QBarCategoryAxis();
        _axisY = new QValueAxis();
        _chartView = new QChartView(_chart);
        QStringList categories;
        _series->append(_set);
        _chart->addSeries(_series);
        _chart->setTitle("");
//        _chart->setAnimationOptions(QChart::SeriesAnimations);
        _chart->setAnimationOptions(QChart::NoAnimation);
        for (int i = 0;i < GetRandomVector().size(); ++i) {
            categories << std::to_string(i).c_str();
        }
        _axisX->append(categories);
        _axisX->setVisible(false);
        _axisY->setVisible(false);
        _chart->addAxis(_axisX, Qt::AlignBottom);
        _series->attachAxis(_axisX);
        _axisY->setRange(0,100);
        _chart->addAxis(_axisY, Qt::AlignLeft);
        _series->attachAxis(_axisY);
        _chart->legend()->setVisible(false);
        _chart->legend()->setAlignment(Qt::AlignBottom);
        _chartView->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(_chartView,0,0,10,10);


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
            _speed = slider->value();
        });

        QObject::connect(start_but,&QPushButton::clicked,[=]{
            if (_start == false) {
                _start = true;
            }
        });
        QObject::connect(pause_but,&QPushButton::clicked,[=]{
            if (_pause == false) {
                _pause = true;
                pause_but->setText("继续");
            }
            else {
                _pause = false;
                pause_but->setText("暂停");
            }
        });
        QObject::connect(stop_but,&QPushButton::clicked,[=]{

        });



    }
    void UpUI() {
        auto vec = this->GetRandomVector();
        auto set = this->GetBarSet();
        set->remove(0,vec.size());
        for (auto num : vec) {
            *set << num;
        }
    }
};

#undef CMP
#undef SORT_FUNC_BASE



#endif
