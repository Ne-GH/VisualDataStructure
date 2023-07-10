/*******************************************************************************
 * Author : yongheng
 * Data   : 2022/06/28 00:21
*******************************************************************************/


#ifndef MSTL_ARRAY_HPP_
#define MSTL_ARRAY_HPP_

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

};  // class MSTL::Array

}   // namespace MSTL


#endif
