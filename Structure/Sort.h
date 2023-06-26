/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/22 17:28
*******************************************************************************/
//

#ifndef VISUALDATASTRUCTURE_SORT_H
#define VISUALDATASTRUCTURE_SORT_H

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
    void UPUI();
private:
    std::vector<int >vec;
public:
    Sort() {
        GetRandomVector(100);
    }
    void begin() {
        std::sort(vec.begin(),vec.end(),[=](const int val1,const int val2){
            emit UPUI();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (val1 < val2)
                return true;
            else
                return false;
        });
    }
    void GetRandomVector(size_t size) {
        vec.resize(10);
        std::default_random_engine rand_engine;
        for (auto &p : vec) {
            p = rand_engine() % 100;
        }
    }
    auto GetRandomVector() {
        return vec;
    }

};





#endif //VISUALDATASTRUCTURE_SORT_H
