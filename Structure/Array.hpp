/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 16:12
*******************************************************************************/

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "./StructureBase.hpp"
#include "../Graphics/GraphicsItem.h"
#include "../Graphics/GraphicsScene.h"

#include <array>
#include <vector>

class Array : public StructureBase<std::vector>{

private:
    GraphicsScene *_scene;
    int _x = 0;
    int _y = 0;

public:
    Array() = default;
    ~Array() = default;
    Array(GraphicsScene *scene) : _scene(scene) {  }


    void Clear(GraphicsScene* scene) {
        scene->clear();
    }

    void Install(GraphicsItem* item) {
        _scene->addItem(item);
        this->_val.push_back(item);
    }

    void Delete(GraphicsItem* item) {
        for (auto it = _val.begin();it != _val.end(); ) {
            if (*it == item) {
                it = _val.erase(it);
            }
            else {
                it ++;
            }
        }
    }

    void Draw(GraphicsScene* scene) {  }
    void Updata(GraphicsItem*) {  }
    GraphicsItem* Search(GraphicsItem* item) {  }
};


#endif // _ARRAY_H_
