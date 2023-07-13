/*
*    Time: 04/10/22 12:56:43
*    Create By yongheng
*/

#ifndef MSTL_STACK_HPP
#define MSTL_STACK_HPP

#include <iostream>
#include "Array.hpp"

namespace MSTL {

template<typename T>
class Stack{
private:
    Arrary<T> _stack;

public:
    
    void Push(T data){
        _stack.PushBack(data);
    }
    T Pop() {
        return _stack.PopBack();
    }
    size_t Size(){
        return _stack.Size();
    }
    T Top(){
        return _stack[_stack.Size()-1];
    }


};

}
#endif
