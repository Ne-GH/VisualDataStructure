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

#include "Sort.hpp"

#define CMP \
    [this](auto val1,auto val2) {\
        emit UPUI();\
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));\
        if (val1 < val2)\
            return true;\
        else\
            return false;\
    }
#define SORT_FUNC_BASE(func) func(vec.begin(),vec.end(),CMP); \
                        emit UPUI();\
                        thread()->quit();
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
};

#undef CMP
#undef SORT_FUNC_BASE



#endif
