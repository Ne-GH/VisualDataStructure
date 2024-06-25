/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/18 12:45
*********************************************************************/
#ifndef MSTLqueue__HPP
#define MSTLqueue__HPP

#include <iostream>
#include "Array.hpp"


namespace MSTL {


template<typename T>
class Queue {
    MSTL::Arrary<T> queue_;

    class iterator {
        T *it;
    public:
        iterator(T *p) {
            it = p;
        }
        T &operator *() {
            return *it;
        }
        bool operator != (const iterator & that) {
            return this->it != that.it;
        }
        size_t operator - (const iterator &that) {
            return it - that.it;
        }
        iterator & operator ++ (){
            ++it;
            return *this;
        }

    };

public:

    void Push(T val) {
        queue_.PushBack(val);
    }

    T Front() {
        return *queue_.begin();
    }

    T Pop(){
        return queue_.FrontBack();
    }

    size_t Size(){
        return queue_.size();
    }

    void Clear() {
        queue_.Clear();
    }
    iterator begin() {
        return iterator(queue_.GetBegin());
    }
    iterator end() {
        return iterator(queue_.GetEnd());
    }
    T operator[] (size_t offset) {
        return queue_.GetBegin()[offset];
    }
};

}
#endif
