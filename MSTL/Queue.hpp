/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/18 12:45
*********************************************************************/
#ifndef MSTL_QUEUE_HPP
#define MSTL_QUEUE_HPP

#include <iostream>
//#include "Array.cppm"
import Array;

namespace MSTL {


template<typename T>
class Queue {
    MSTL::Arrary<T> _queue;

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
        _queue.PushBack(val);
    }

    T Front() {
        return *_queue.begin();
    }

    T Pop(){
        return _queue.FrontBack();
    }

    size_t Size(){
        return _queue.Size();
    }

    void Clear() {
        _queue.Clear();
    }
    iterator begin() {
        return iterator(_queue.GetBegin());
    }
    iterator end() {
        return iterator(_queue.GetEnd());
    }
    T operator[] (size_t offset) {
        return _queue.GetBegin()[offset];
    }
};

}
#endif
