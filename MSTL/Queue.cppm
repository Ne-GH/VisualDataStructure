/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/18 12:45
*********************************************************************/

module;
#include "iostream"
export module Queue;

import Array;
//#include "Array.cppm"

export namespace MSTL {


template<typename T>
class Queue {
    MSTL::Array<T> _queue;

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
