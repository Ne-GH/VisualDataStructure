
#ifndef MSTL_LIST_HPP
#define MSTL_LIST_HPP

#include <iostream>

namespace MSTL {
template<typename T>
class List{
private:

    class Node{
    public:
        Node() { }
        Node(T data):data(data) { }
        T data;
        Node *next;
    };

    class iterator {
        Node *it;
    public:

        iterator(Node *p) : it(p) {  }
        iterator &operator ++() {
            it = it->next;
            return *this;
        }
        bool operator != (const iterator& that) {
            return this->it != that.it;
        }
        T &operator * () {
            return it->data;
        }

    };


    size_t list_len_= 0;

    Node *head_;
    Node *end_;

    /*******************************************************************************
     * 会把构造函数中创建的head_node一并删除
    *******************************************************************************/
    void  _Clear(_Node *p) {
        if (p == nullptr)
            return;
        else if (p->next == nullptr) {
            delete p;
            return;
        }
        _Clear(p->next);
        delete p;
    }

public:

    List() {
        auto head_node = new _Node(0);
        head_ = end_ = head_node;
        end_->next = nullptr;
        list_len_ = 0;
    }

    ~List(){
        Clear();
        if (head_ != nullptr)
            delete head_;
        head_ = end_ = nullptr;
        list_len_ = 0;
    }

    void PushBack(T data) {
        auto node = new Node(data);
        end_->next = node;
        end_ = node;
        end_->next = nullptr;
        list_len_ ++;
    }

    void Clear() {
        _Clear(head_->next);
        head_->next = nullptr;
        end_ = head_;
        list_len_ = 0;
    }

    /*******************************************************************************
     * 插入一个节点，使之下标成为insert_pos
    *******************************************************************************/
    void Insert(size_t insert_pos,T data){
        if(insert_pos < 0 || insert_pos > list_len_+1){
            std::cerr << "pos: " << insert_pos << "is error" << std::endl;
            return;
        }
        auto tmp = head_;
        int pos = 0;
        while (pos++ < insert_pos) {
            tmp = tmp->next;
        }
        tmp->next = end_ = new Node(data);
        end_->next = nullptr;
        list_len_ ++;
    }


    /*******************************************************************************
     * delete 的参数和Insert的参数对应，删除下标为x的元素,下标从0开始
    *******************************************************************************/
    void Delete(size_t del_pos){
        if (del_pos < 0 || del_pos >= list_len_) {
            std::cerr << "pos: " << del_pos << "is error" << std::endl;
            return;
        }
        int pos = 0;
        auto tmp = head_;
        auto cur = head_->next;
        while (pos ++ < del_pos) {
            tmp = cur;
            cur = cur->next;
        }
        tmp->next = tmp->next->next;
        delete cur;

        if (list_len_ == pos) {
            end_ = tmp;
            end_->next = nullptr;
        }
        list_len_ --;

    }


    // head 和 end一定不为空，因为创建了head_node
    iterator begin(){
        return iterator(head_->next);
    }
    iterator end(){
        return iterator(end_->next);
    }

    size_t Size(){
        return list_len_;
    }
    
};

}
#endif