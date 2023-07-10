/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/22 17:28
*******************************************************************************/
//

#ifndef _VISUALSORT_H_
#define _VISUALSORT_H_

#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
#include <QThread>

#include "Sort.hpp"

#define CMP \
    [=](auto val1,auto val2) {\
        emit UPUI();\
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));\
        if (val1 < val2)\
            return true;\
        else\
            return false;\
    }
class VisualSort : public QObject {
    Q_OBJECT

signals:
    void UPUI();
private:
    std::vector<int >vec;
    int sleep_time = 10;


public:

    VisualSort() {
        GetRandomVector(100);
    }

    void BubbleSort() {
        MSTL::bubble_sort(vec.begin(), vec.end(), CMP);
        thread()->quit();
    }
    void StdSort() {
        std::sort(vec.begin(),vec.end(),CMP);
        thread()->quit();
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
};

#undef CMP




#endif
