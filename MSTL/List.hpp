
#ifndef MSTL_LIST_HPP
#define MSTL_LIST_HPP

#include <iostream>

namespace MSTL {
template<typename T>
class List{
private:

    class _Node{
    public:
        _Node() { }
        _Node(T data):data(data) { }
        T data;
        _Node *_next;
    };

    class iterator {
        _Node *it;
    public:

        iterator(_Node *p) : it(p) {  }
        iterator &operator ++() {
            it = it->_next;
            return *this;
        }
        bool operator != (const iterator& that) {
            return this->it != that.it;
        }
        T &operator * () {
            return it->data;
        }

    };


    size_t _list_len= 0;

    _Node *_head;
    _Node *_end;

    /*******************************************************************************
     * 会把构造函数中创建的head_node一并删除
    *******************************************************************************/
    void  _Clear(_Node *p) {
        if (p == nullptr)
            return;
        else if (p->_next == nullptr) {
            delete p;
            return;
        }
        _Clear(p->_next);
        delete p;
    }

public:

    List() {
        auto head_node = new _Node(0);
        _head = _end = head_node;
        _end->_next = nullptr;
        _list_len = 0;
    }

    ~List(){
        Clear();
        if (_head != nullptr)
            delete _head;
        _head = _end = nullptr;
        _list_len = 0;
    }

    void PushBack(T data) {
        auto node = new _Node(data);
        _end->_next = node;
        _end = node;
        _end->_next = nullptr;
    }

    void Clear() {
        _Clear(_head->_next);
        _head->_next = nullptr;
        _end = nullptr;
        _list_len = 0;
    }

    /*******************************************************************************
     * 插入一个节点，下标从1开始
    *******************************************************************************/
    void Insert(size_t pos,T data){
        // pos == 1, end = head;
        // link_lin = 0;
        if(pos <= 0 ||pos > _list_len+1){
            std::cerr << "pos: " << pos << "is error" << std::endl;
            return;
        }

        int cnt = 0;
        pos--;
        _Node *tmp = _head;

        _Node *q = new _Node(data);

        while(cnt++ < pos){
            tmp = tmp->_next;
        }

        q->_next = tmp->_next;
        tmp->_next = q;

        if(pos == _list_len){
            _end = tmp->_next;
        }

        _list_len ++;

    }


    void Delete(size_t pos){

        if(pos == 0){
            _Node *tmp = _head;
            _head = _head->_next;
            delete tmp;
            _list_len --;
            return;
        }

        if(pos < 0 || pos > _list_len){
//            OUT_ERROR("pos" << pos << "is error");
            exit(0);
        }

        _Node *tmp = _head;
        pos--;
        size_t cnt = 0;
        while(cnt++ < pos){
            tmp = tmp->_next;
        }
        _Node *q = tmp->_next;
        tmp->_next = tmp->_next->_next;

        if(cnt == _list_len){
            _end = tmp;
        }

        delete q;
        _list_len --;

    }

    void Pop_back(){
        Delete(this->_list_len);
    }
    T *Find_val_by_pos(size_t pos){

        if(pos <= 0 || pos > _list_len){
//            OUT_ERROR("pos" << pos << "is error");
            return nullptr;
        }

        _Node *tmp = _head;

        size_t cnt = 0;
        while(cnt++ < pos){
            tmp = tmp->_next;
        }

        return &(tmp->data);
    }

    size_t Find_pos_by_val(T val){
        _Node *tmp = _head->_next;

        size_t cnt = 1;
        while(tmp){
            if(tmp->data == val){
                return cnt;
            }
            cnt ++;
            tmp = tmp->_next;

        }
        return 0;
    }



    
    T Front(){
        T *p = begin();
        if(p != nullptr){
            return *p;
        }
        else{
//            OUT_ERROR("This List is empty");
        }
        exit(0);
    }

    // head 和 end一定不为空，因为创建了head_node
    iterator begin(){
        return iterator(_head->_next);
    }
    iterator end(){
        return iterator(_end->_next);
    }

    size_t Size(){
        return _list_len;
    }
    
};

}
#endif