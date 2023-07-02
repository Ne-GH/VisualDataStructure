/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/18 13:59
*********************************************************************/
#ifndef _MAP_HPP_
#define _MAP_HPP_

#include "BinaryTree.hpp"

namespace MSTL {

template<typename KEY,typename VAL>
class Pair{
public:
    KEY _key;
    VAL _val;

    friend std::ostream & operator << (std::ostream &out,Pair pair){
        std::cout << pair._key << ":" << pair._val;
        return out;
    }
    Pair(){
        _key = _val = 0;
    }
    Pair(KEY key,VAL val) : _key(key),_val(val){  }


    bool operator < (Pair r){
        if(this->_key < r._key){
            return true;
        }
        return false;
    }
    bool operator > (Pair r){
        return !(*this < r);
    }
    bool operator == (Pair r){
        if(this->_key == r._key){
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

    BinaryTree<Pair<KEY,VAL>> _map;
public:

    Map(){
    }
    ~Map(){
    }

    void Insert(KEY key,VAL val){
        auto pair = Pair<KEY,VAL>(key,val);
        _map.Insert(pair);
    }

    VAL& operator [](KEY key){
        auto pair = Pair<KEY,VAL>();
        pair._key = key;
        auto p = _map.Search(pair);
        if(p == nullptr){
            VAL val = VAL();
            _map.Insert(Pair<KEY,VAL>(key,val));
            p = _map.Search(pair);
            return p->_val._val;
        }
        else{
            return p->_val._val;
        }

    }
    void Delete(KEY key){
        Pair<KEY,VAL> pair(key,0);
        _map.Delete(pair);
    }
    void Draw(){
        _map.Draw();
    }

};
}
#endif //DATASTRUCTURE_MAP_H
