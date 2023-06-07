/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/05 23:06
*******************************************************************************/

#ifndef _Arrary_H_
#define _Arrary_H_

#include "StructureBase.hpp"
#include <vector>
#include <tuple>

class Arrary : public StructureBase<std::vector>{
    CustomScene *_scene;
    int _x = 0;
    int _y = 0;

public:
    Arrary() = default;
    ~Arrary() = default;
    Arrary(CustomScene *scene) : _scene(scene) {  }


    void Clear(CustomScene* scene) {
        scene->clear();
    }

    void Install(CustomItem* item) {

        _scene->addItem(item);
        this->_val.push_back(item);
    }

    void Delete(CustomItem* item) {
        for (auto it = _val.begin();it != _val.end(); ) {
            if (*it == item) {
                it = _val.erase(it);
            }
            else {
                it ++;
            }
        }
    }

    void Draw(CustomScene* scene) {  }
    void Updata(CustomItem*) {  }
    CustomItem* Search(CustomItem* item) {  }
};


#endif // _Arrary_H_
