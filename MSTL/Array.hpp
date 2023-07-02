/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/28 00:21
*******************************************************************************/


#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_


namespace MSTL{
template<typename T>
class Arrary{
private:
    T *_arr;
    size_t _memory_size = 10;
    size_t _data_len = 0;

    void re_new(size_t new_memory_size){

        T *tmp = new T[new_memory_size]();
        for(int i = 0;i < _data_len; ++i){
            new (&tmp[i]) T(_arr[i]);
        }
        delete _arr;

        _memory_size = new_memory_size;
        _arr = tmp;
    }

public:


    Arrary(){
        _arr = new T[_memory_size];
    }
    ~Arrary(){
        delete _arr;
    }

    void Insert(int pos,T val){
        if(pos <= 0 || pos > _data_len+1){
            std::cerr << "pos : " << pos << "is error";
            return;
        }

        if(_data_len+1 >= _memory_size){
            re_new(_memory_size*3.0/2);
        }

        int i;

        _data_len ++;
        for(i = _data_len;i >= pos; --i){
            _arr[i] = _arr[i-1];
        }
        _arr[i] = val;
    }

    void Push_back(T num){
        if(_data_len+1 >= _memory_size){
            re_new(_memory_size*3.0/2);
        }
        _arr[_data_len++] = num;
    }

    T Pop_back(){
        if(_data_len <= _memory_size/2){
            re_new(_memory_size*2.0/3);
        }
        _data_len--;
        return _arr[_data_len];
    }
    T Pop(){
        return Pop_back();
    }
    void Delete(int pos){

        if(pos <= 0 || pos > _data_len){
            std::cerr << "Delete pos " << pos << "is error";
            return;
        }

        int i = 0;
        for(i = pos-1 ;i < _data_len; ++i){
            _arr[i] = _arr[i+1];
        }
        _data_len --;

        if(_data_len <= _memory_size/2){
            re_new(_memory_size*2.0/3);
        }

    }

    void Updata(T oldval,T newval){
        size_t pos = Find_line(oldval);

        if(pos != 0){
            _arr[pos-1] = newval;
        }
    }

    size_t Find_line(T val){

        for(int i = 0;i < _data_len; ++i){
            if(_arr[i] == val)
                return i + 1;
        }

        // return val position
        // so pos lagger than 0
        return 0;
    }

    size_t Find_binarySearch(T val){

        int mid;
        int left = 0,right = _data_len-1;

        while(left <= right){
            mid = left + (right-left)/2;

            if(_arr[mid] < val)
                left = mid + 1;
            else if(_arr[mid] > val)
                right = mid - 1;
            else
                return mid + 1;
        }

        return 0;
    }

    void Show(){
        for(int i = 0;i < _data_len; ++i){
            std::cout << _arr[i] << " ";
        }
    }
    void Print(){
        Show();
    }

    size_t Size(){
        return _data_len;
    }

    T Front(){
        return *begin();
    }
    T End(){
        return *(end()-1);
    }


    T *begin(){
        return _arr;
    }

    T *end(){
        return _arr + _data_len;
    }
};

}


#endif
