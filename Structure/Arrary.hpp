/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/05 23:06
*******************************************************************************/

#ifndef _Arrary_H_
#define _Arrary_H_

#include "StructureBase.hpp"
#include <vector>


template <typename T>
class Arrary : public StructureBase<std::vector,T>{

public:
    Arrary() = default;
    ~Arrary() = default;

    void Draw(CustomScene* scene) {
        for (auto& item : this->_val) {
            scene->addItem(item);
        }
    }
    void Clear(CustomScene*) {

    }
    void Install(T item) {
        this->_val.push_back(item);
    }
    void Delete(T*) {

    }
    void Updata(T*) {

    }
    void Search(T*) {

    }
};


#endif // _Arrary_H_
