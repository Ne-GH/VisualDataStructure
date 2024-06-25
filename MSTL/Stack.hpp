/*
*    Time: 04/10/22 12:56:43
*    Create By yongheng
*/

#ifndef MSTLstack__HPP
#define MSTLstack__HPP

#include <iostream>
#include "Array.hpp"

namespace MSTL {

template<typename T>
class Stack{
private:
    Arrary<T> stack_;
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
        stack_.PushBack(data);
    }
    T Pop() {
        return stack_.PopBack();
    }
    size_t Size(){
        return stack_.size();
    }
    T Top(){
        return stack_[stack_.Size()-1];
    }
    iterator begin() {
        return iterator(stack_.GetBegin());
    }
    iterator end() {
        return iterator(stack_.GetEnd());
    }
    T operator[] (size_t offset) {
        return stack_.GetBegin()[offset];
    }
};

}
#endif
