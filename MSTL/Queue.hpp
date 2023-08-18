/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/18 12:45
*********************************************************************/
#ifndef MSTL_QUEUE_HPP
#define MSTL_QUEUE_HPP

#include <iostream>
#include "Array.hpp"


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
    Queue(){
        _queue = Arrary<T>();
    }
    ~Queue(){

    }

    void Push(T val) {
        _queue.PushBack(val);
    }

    T& Front() {
        return *_queue.begin();
    }

    T Pop(){
        T ret = Front();
        _queue.Delete(0);
        return ret;
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
