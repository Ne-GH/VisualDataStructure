/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/18 12:45
*********************************************************************/
#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include "List.hpp"


namespace MSTL {


template<typename T>
class Queue {
private:
    List<T> _queue;
public:
    Queue(){
        _queue = List<T>();
    }
    ~Queue(){

    }

    void Push_back(T val){
        _queue.Push_back(val);
        return;
    }

    T Pop_front(){
        T ret = _queue.Front();
        _queue.Delete(0);
        return ret;
    }

    T Front(){
        return _queue.Front();
    }

    size_t Size(){
        return _queue.Size();
    }

};

}
#endif
