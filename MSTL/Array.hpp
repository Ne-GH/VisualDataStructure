/*******************************************************************************
 * Author : yongheng
 * Data   : 2022/06/28 00:21
*******************************************************************************/


#ifndef MSTL_ARRAY_HPP
#define MSTL_ARRAY_HPP

namespace MSTL{
template<typename T>
class Arrary{

    class iterator {
        T *it_;
    public:
        explicit iterator(T *p) {
            it_ = p;
        }
        T &operator *() {
            return *it_;
        }
        bool operator != (const iterator & that) {
            return this->it_ != that.it_;
        }
        size_t operator - (const iterator &that) {
            return it_ - that.it_;
        }
        iterator & operator ++ (){
            ++it_;
            return *this;
        }
    };


    T *arr_;
    size_t memory_size_ = 10;
    size_t data_len_ = 0;

    void realloc(const size_t newmemory_size_) {
        arr_ = static_cast<T *>(std::realloc(arr_,newmemory_size_*sizeof(T)));
        if (arr_ == nullptr) {
            throw std::bad_alloc();
        }
    }
    size_t ReallocUpSize() {
        memory_size_ = memory_size_*3/2;
        return memory_size_;
    }
    size_t ReallocDownSize() {
        memory_size_ = memory_size_*2/3;
        return memory_size_;
    }
    void ReallocUp() {
        if (data_len_ == memory_size_) {
            realloc(ReallocUpSize());
        }
    }
    void ReallocDown() {
        if (data_len_ <= memory_size_/2) {
            realloc(ReallocDownSize());
        }
    }

public:

    Arrary(){
        arr_ = new T[memory_size_];
    }
    ~Arrary(){
        ::free(arr_);
    }

    void PushBack(T val){
        ReallocUp();
        arr_[data_len_++] = val;
    }
    T PopBack() {
        T pop_val = arr_[data_len_-1];
        data_len_ --;
        ReallocDown();
        return pop_val;
    }
    T FrontBack() {
        if (data_len_ == 0) {
            std::cerr << "队列为空,不能进行出队" << std::endl;
            exit(-1);
        }
        T front_val = arr_[0];
        for (int i = 0;i < data_len_-1; ++i) {
            arr_[i] = arr_[i+1];
        }
        data_len_ --;
        ReallocDown();
        return front_val;
    }
    iterator Delete(iterator del_addr) {
        size_t offset = del_addr - iterator(arr_);
        while (offset+1 < data_len_) {
            arr_[offset] = arr_[offset + 1];
            ++offset;
        }
        data_len_ --;
        ReallocDownSize();
        if (offset > data_len_) {
            return end();
        }
        else {
            return iterator(arr_ + offset);
        }
    }
    /*******************************************************************************
     * 按照下标进行删除
    *******************************************************************************/
    void Delete(size_t pos) {
        if (pos < 0 || pos >= data_len_) {
            std::cerr << "bad pos" << std::endl;
        }
        for (int i = pos;i < data_len_-1; ++i) {
            arr_[pos] = arr_[pos+1];
        }
        data_len_--;
        ReallocDownSize();
    }
    [[nodiscard("get size not use")]]
    size_t size() const {
        return data_len_;
    }
    iterator begin() {
        return iterator(arr_);
    }
    iterator end() {
        return iterator(arr_ + data_len_);
    }

    T *GetBegin() {
        return arr_;
    }
    T *GetEnd() {
        return arr_ + data_len_;
    }
    T operator[] (size_t offset) {
        return arr_[offset];
    }

};  // class MSTL::Array

}   // namespace MSTL


#endif
