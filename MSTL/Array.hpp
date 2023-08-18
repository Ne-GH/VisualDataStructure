/*******************************************************************************
 * Author : yongheng
 * Data   : 2022/06/28 00:21
*******************************************************************************/


#ifndef MSTL_ARRAY_HPP
#define MSTL_ARRAY_HPP

namespace MSTL{
template<typename T>
class Arrary{
private:

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


    T *_arr_address;
    size_t _memory_size = 10;
    size_t _data_len = 0;

    void Realloc(size_t new_memory_size) {
        _arr_address = (T *)::realloc((void *)_arr_address,new_memory_size*sizeof(T));
        if (_arr_address == nullptr) {
            throw std::bad_alloc();
        }
    }
    size_t ReallocUpSize() {
        _memory_size = _memory_size*3/2;
        return _memory_size;
    }
    size_t ReallocDownSize() {
        _memory_size = _memory_size*2/3;
        return _memory_size;
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
        _arr_address = (T *)::malloc(_memory_size*sizeof(T));
    }
    ~Arrary(){
        ::free(_arr_address);
    }

    void PushBack(T val){
        ReallocUp();
        _arr_address[_data_len++] = val;
    }
    T PopBack() {
        T pop_val = _arr_address[_data_len-1];
        _data_len --;
        ReallocDown();
        return pop_val;
    }
    T FrontBack() {
        if (_data_len == 0) {
            std::cerr << "队列为空,不能进行出队" << std::endl;
            exit(-1);
        }
        T front_val = _arr_address[0];
        for (int i = 0;i < _data_len-1; ++i) {
            _arr_address[i] = _arr_address[i+1];
        }
        _data_len --;
        ReallocDown();
        return front_val;
    }
    iterator Delete(iterator del_addr) {
        size_t offset = del_addr - iterator(_arr_address);
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
            return iterator(_arr_address + offset);
        }
    }
    /*******************************************************************************
     * 按照下标进行删除
    *******************************************************************************/
    void Delete(size_t pos) {
        if (pos < 0 || pos >= _data_len) {
            std::cerr << "bad pos" << std::endl;
        }
        for (int i = pos;i < _data_len-1; ++i) {
            _arr_address[pos] = _arr_address[pos+1];
        }
        _data_len --;
        ReallocDownSize();
        return;
    }
    size_t Size() {
        return _data_len;
    }
    iterator begin() {
        return iterator(_arr_address);
    }
    iterator end() {
        return iterator(_arr_address + _data_len);
    }

    T *GetBegin() {
        return _arr_address;
    }
    T *GetEnd() {
        return _arr_address + _data_len;
    }
    T operator[] (size_t offset) {
        return _arr_address[offset];
    }

};  // class MSTL::Array

}   // namespace MSTL


#endif
