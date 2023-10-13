
module ;
#include <iostream>
export module List;

export namespace MSTL {
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
        _list_len ++;
    }

    void Clear() {
        _Clear(_head->_next);
        _head->_next = nullptr;
        _end = _head;
        _list_len = 0;
    }

    /*******************************************************************************
     * 插入一个节点，使之下标成为insert_pos
    *******************************************************************************/
    void Insert(size_t insert_pos,T data){
        if(insert_pos < 0 || insert_pos > _list_len+1){
            std::cerr << "pos: " << insert_pos << "is error" << std::endl;
            return;
        }
        auto tmp = _head;
        int pos = 0;
        while (pos++ < insert_pos) {
            tmp = tmp->_next;
        }
        tmp->_next = _end = new _Node(data);
        _end->_next = nullptr;
        _list_len ++;
    }


    /*******************************************************************************
     * delete 的参数和Insert的参数对应，删除下标为x的元素,下标从0开始
    *******************************************************************************/
    void Delete(size_t del_pos){
        if (del_pos < 0 || del_pos >= _list_len) {
            std::cerr << "pos: " << del_pos << "is error" << std::endl;
            return;
        }
        int pos = 0;
        auto tmp = _head;
        auto cur = _head->_next;
        while (pos ++ < del_pos) {
            tmp = cur;
            cur = cur->_next;
        }
        tmp->_next = tmp->_next->_next;
        delete cur;

        if (_list_len == pos) {
            _end = tmp;
            _end->_next = nullptr;
        }
        _list_len --;

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