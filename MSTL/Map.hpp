/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/18 13:59
*********************************************************************/
#ifndef MSTLmap__HPP
#define MSTLmap__HPP

#include "BinaryTree.hpp"

namespace MSTL {

template<typename KEY,typename VAL>
class Pair{
public:
    KEY key_;
    VAL val_;

    friend std::ostream & operator << (std::ostream &out,Pair pair){
        std::cout << pair.key_ << ":" << pair.val_;
        return out;
    }
    Pair(){
        key_ = val_ = 0;
    }
    Pair(KEY key,VAL val) : key_(key),val_(val){  }


    bool operator < (Pair r){
        if(this->key_ < r.key_){
            return true;
        }
        return false;
    }
    bool operator > (Pair r){
        return !(*this < r);
    }
    bool operator == (Pair r){
        if(this->key_ == r.key_){
            return true;
        }
        return false;
    }
    bool operator != (Pair r){
        return !(*this == r);
    }
};

/* K and V need operator < > == */
template<typename KEY,typename VAL>
class Map{
private:

    BinaryTree<Pair<KEY,VAL>> map_;
public:

    Map(){
    }
    ~Map(){
    }

    void Insert(KEY key,VAL val){
        auto pair = Pair<KEY,VAL>(key,val);
        map_.Insert(pair);
    }

    VAL& operator [](KEY key){
        auto pair = Pair<KEY,VAL>();
        pair.key_ = key;
        auto p = map_.Search(pair);
        if(p == nullptr){
            VAL val = VAL();
            map_.Insert(Pair<KEY,VAL>(key,val));
            p = map_.Search(pair);
            return p->val_.val_;
        }
        else{
            return p->val_.val_;
        }

    }
    void Delete(KEY key){
        Pair<KEY,VAL> pair(key,0);
        map_.Delete(pair);
    }
    void Draw(){
        map_.Draw();
    }

};
}
#endif //DATASTRUCTUREmap__H
