/*
*    Time: 04/10/22 12:56:43
*    Create By yongheng
*/

#ifndef MSTL_STACK_HPP
#define MSTL_STACK_HPP

#include <iostream>
//#include "Array.cppm"

import Array;

namespace MSTL {

template<typename T>
class Stack{
private:
    Arrary<T> _stack;
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
    iterator begin() {
        return iterator(_stack.GetBegin());
    }
    iterator end() {
        return iterator(_stack.GetEnd());
    }
    T operator[] (size_t offset) {
        return _stack.GetBegin()[offset];
    }
};

}
#endif
