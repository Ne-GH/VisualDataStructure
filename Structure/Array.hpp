/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 16:12
*******************************************************************************/

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "./StructureBase.hpp"
#include "../Graphics/GraphicsItem.h"
#include "../Graphics/GraphicsScene.h"
#include "../Logs/Log.h"

#include <array>
#include <vector>

#include <QMetaType>



class Array : public QObject, public StructureBase<std::vector>{
    Q_OBJECT


private:
    GraphicsScene *_scene;
    int _x = 0;
    int _y = 0;
    using StructureBase<std::vector>::_val;
public:
    int x = 0;
    Array() = default;
    ~Array() = default;
    Array(GraphicsScene *scene) : _scene(scene) {
        int scene_width = _scene->width();
        int scene_height = _scene->height();

        x = 10;

        _y = scene_height * 0.3;
        _x = scene_width / 2;
    }


    void Clear(GraphicsScene* scene) {
        scene->clear();
    }

    void Push_back(int val) {
        Insert(val);
    }
    void Insert(GraphicsItem* item) {
        QObject::connect(item,&GraphicsItem::Selected,[&](auto pitem){
            for (auto it : _val) {
                it->setSelected(true);
            }
//            std::cout << _val.size() << std::endl;
//            std::cout << x << std::endl;
        });
        _scene->addItem(item);
        this->_val.push_back(item);
        item->InputVal();
    }
    // TODO int => T
    void Insert(int val) {
        auto p = new GraphicsItem(0,0,100,100);
        int install_x,install_y;
        if (_val.size() == 0) {
            install_x = _x;
            install_y = _y;
        }
        else {
            std::tie(install_x,install_y) = _val[_val.size()-1]->GetPos();
            auto [w,h] = _val[_val.size()-1]->GetWH();
            install_x += w;
        }

        p->SetPos(install_x,install_y);
        p->SetVal(val);
        Insert(p);
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
