/*******************************************************************************
 * Author : yongheng
 * Data   : 2022/06/28 00:21
*******************************************************************************/


#ifndef MSTL_ARRAY_HPP_
#define MSTL_ARRAY_HPP_

#include <iterator>

namespace MSTL{
template<typename T>
class Arrary{
private:
    T *_arr_address;
    size_t _memory_size = 10;
    size_t _data_len = 0;

    void Realloc(size_t new_memory_size) {
        _arr_address = (T *)::realloc((void *)_arr_address,new_memory_size);
        if (_arr_address == nullptr) {
            throw std::bad_alloc();
        }
    }
    size_t ReallocUpSize() {
        return _memory_size*3 / 2;
    }
    size_t ReallocDownSize() {
        return _memory_size*2 / 3;
    }
    void ReallocUp() {
        if (_data_len == _memory_size) {
            Realloc(ReallocUpSize());
        }
    }
    void ReallocDown() {
        if (_data_len <= _memory_size/2) {
            Realloc(ReallocDownSize());
        }
    }

public:

    Arrary(){
        _arr_address = (T *)::malloc(_memory_size);
    }
    ~Arrary(){
        ::free(_arr_address);
    }

    void PushBack(T val){
        ReallocUp();
        _arr_address[_data_len++] = val;
    }
    T PopBack() {
        T pop_val = _arr_address[_data_len];
        _data_len --;
        ReallocDown();
        return pop_val;
    }
    T* Delete(T *del_addr) {
        size_t offset = del_addr - _arr_address;
        while (offset+1 < _data_len) {
            _arr_address[offset] = _arr_address[offset + 1];
            ++offset;
        }
        _data_len --;
        ReallocDownSize();
        if (offset > _data_len) {
            return end();
        }
        else {
            return _arr_address + offset;
        }
    }
    size_t Size() {
        return _data_len;
    }
    T* begin() {
        return _arr_address;
    }
    T* end() {
        return _arr_address + _data_len;
    }

    T operator[] (size_t offset) {
        return _arr_address[offset];
    }
//    void Delete(int pos){
//
//        if(pos <= 0 || pos > _data_len){
//            std::cerr << "Delete pos " << pos << "is error";
//            return;
//        }
//
//        int i = 0;
//        for(i = pos-1 ;i < _data_len; ++i){
//            _arr[i] = _arr[i+1];
//        }
//        _data_len --;
//
//        if(_data_len <= _memory_size/2){
//            re_new(_memory_size*2.0/3);
//        }
//
//    }

//    void Updata(T oldval,T newval){
//        size_t pos = Find_line(oldval);
//
//        if(pos != 0){
//            _arr[pos-1] = newval;
//        }
//    }
//
//    size_t Find_line(T val){
//
//        for(int i = 0;i < _data_len; ++i){
//            if(_arr[i] == val)
//                return i + 1;
//        }
//
//        // return val position
//        // so pos lagger than 0
//        return 0;
//    }

//    size_t Find_binarySearch(T val){
//
//        int mid;
//        int left = 0,right = _data_len-1;
//
//        while(left <= right){
//            mid = left + (right-left)/2;
//
//            if(_arr[mid] < val)
//                left = mid + 1;
//            else if(_arr[mid] > val)
//                right = mid - 1;
//            else
//                return mid + 1;
//        }
//
//        return 0;
//    }
//
//    void Show(){
//        for(int i = 0;i < _data_len; ++i){
//            std::cout << _arr[i] << " ";
//        }
//    }
//    void Print(){
//        Show();
//    }
//
//    T Front(){
//        return *begin();
//    }
//    T End(){
//        return *(end()-1);
//    }



};

}


#endif
