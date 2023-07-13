/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/18 12:45
*********************************************************************/
#ifndef MSTL_QUEUE_HPP
#define MSTL_QUEUE_HPP

#include "List.hpp"


namespace MSTL {


template<typename T>
class Queue {
private:
    MSTL::List<T> _queue;
public:
    Queue(){
        _queue = List<T>();
    }
    ~Queue(){

    }

    void PushBack(T val) {
        _queue.PushBack(val);
    }

    T& Front() {
        return *_queue.begin();
    }

    T PopFront(){
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

};

}
#endif
