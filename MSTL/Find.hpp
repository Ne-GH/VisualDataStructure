/*********************************************************************
 * Auther : yongheng
 * Date : 2022/11/12 03:54
*********************************************************************/
#ifndef MSTL_FIND_HPP
#define MSTL_FIND_HPP

#include <vector>

namespace MSTL{

template <typename T>
class Find{
    T QueueFind(const T&val);
    std::vector<T> QueueFind_All(const T &val);

    T BinaryFind(const T &val);
};



template<typename T>
T Find<T>::QueueFind(const T &val) {
    return nullptr;
}

template<typename T>
std::vector<T> Find<T>::QueueFind_All(const T &val) {
    return std::vector<T>();
}

}


#endif