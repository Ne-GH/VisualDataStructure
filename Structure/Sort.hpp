/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/22 17:28
*******************************************************************************/
//

#ifndef VISUALDATASTRUCTURE_SORT_HPP
#define VISUALDATASTRUCTURE_SORT_HPP

#include <vector>
#include <map>
#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>

class Sort : public QObject {
    Q_OBJECT

signals:
    void Compare();
    void Updata();

private:

    std::vector<std::pair<QBarSet *,int>> _rand_vec;
    std::vector<int >vec;
    MainWindow *_window = nullptr;
    QChart *_chart = nullptr;
    QChartView * _view = nullptr;
    QBarSeries *_series = nullptr;

public:
    Sort(MainWindow *window) {
        GetRandomVector(100);
    }

    void Show(MainWindow *window) {
        if (_chart != nullptr) {
            delete _chart;
            _chart = nullptr;
        }
        if (_view != nullptr) {
            delete _view;
            _view = nullptr;
        }
        if (_series != nullptr) {
            delete _series;
            _series = nullptr;
        }
        auto view = new QChartView();
        auto series = new QBarSeries();
        auto chart = new QChart();
        window->setCentralWidget(view);

        for (auto num : vec) {
            auto bar = new QBarSet("");
            *bar << num;
            bar->setColor(QColorConstants::Svg::orange);
            series->append(bar);
        }


        view->setChart(chart);
        chart->addSeries(series);
        chart->legend()->hide();
        view->show();

        chart->update();
        view->repaint();
    }
    void begin() {
//        std::sort(_rand_vec.begin(),_rand_vec.end(),[=](std::pair<QBarSet *, int> p1, std::pair<QBarSet *,int> p2){
//            emit Updata();
//            std::this_thread::sleep_for(std::chrono::milliseconds(500));
//            if (p1.second < p2.second) {
//                return true;
//            }
//            else {
//                return false;
//            }
//        });
        std::sort(vec.begin(),vec.end(),[=](const int val1,const int val2){
            emit Updata();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if (val1 < val2)
                return true;
            else
                return false;

        });

    }

    void GetRandomVector(size_t size) {
//        _rand_vec.resize(size);
        vec.resize(100);
        std::default_random_engine rand_engine;

        for (auto &p : vec) {
            p = rand_engine() % 100;
        }

//        for (auto& [bar,num] : _rand_vec) {
//            num = rand() % 100;
//            bar = new QBarSet("");
//            *bar << num;
//        }
    }

};





#endif //VISUALDATASTRUCTURE_SORT_HPP
