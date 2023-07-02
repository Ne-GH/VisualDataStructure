/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/03 00:51
*******************************************************************************/


#ifndef _VisualList_H_
#define _VisualList_H_

#include "VisualStructureBase.hpp"
#include "GraphicsItem.h"
#include "GraphicsScene.h"
#include "Log.h"

#include <vector>

class VisualList : public QObject, public VisualStructureBase<std::vector> {
    Q_OBJECT
private:


private:
    GraphicsScene *_scene;
    int _x = 0;
    int _y = 0;
    using VisualStructureBase<std::vector>::_val;
public:
    VisualList() = default;
    ~VisualList() = default;
    VisualList(GraphicsScene *scene) : _scene(scene) {
            int scene_width = _scene->width();
            int scene_height = _scene->height();

            _y = scene_height * 0.3;
            _x = scene_width / 2;
    }


    void Clear(GraphicsScene* scene) {
        scene->clear();
    }

    void Push_back(int val) {
        Insert(val);
    }
    // pos是删除元素的下标
    void ReMove() {
        for (int i = 1;i < _val.size(); ++i) {
            auto [x,y] = _val[i-1]->GetPos();
            auto [w,h] = _val[i-1]->GetWH();
            _val[i]->SetPos(x+w,y);
        }
        _scene->update();
    }
    void Insert(GraphicsItem* item) {
        QObject::connect(item,&GraphicsItem::LeftSelected,[&](auto pitem){
            for (auto it : _val) {
                it->setSelected(true);
            }
//            std::cout << _val.size() << std::endl;
//            std::cout << x << std::endl;
        });
        QObject::connect(item,&GraphicsItem::RightSelected,[&](auto pitem){
            for (auto it = _val.begin();it != _val.end(); ++it) {
                if (*it == pitem) {
                    _val.erase(it);
                    break;
                }
            }
            _scene->removeItem(pitem);
            delete pitem;

            for (auto p : _val) {
                auto [x,y] = p->GetPos();
                std::cout << x << " " << y << std::endl;
            }
            std::cout << std::endl;
            ReMove();
        });
        _scene->addItem(item);
        this->_val.push_back(item);
        item->InputVal();
    }
    void Insert(int val) {
        auto p = new GraphicsItem(0,0,100,100,GraphicsItem::Ellipse);
        int install_x,install_y;
        if (_val.size() == 0) {
            install_x = _x;
            install_y = _y;
        }
        else {
            std::tie(install_x,install_y) = _val[_val.size()-1]->GetPos();
            std::cout << "" << install_x << " " << install_y << std::endl;
            auto [w,h] = _val[_val.size()-1]->GetWH();
            install_x += w;
        }

        p->SetPos(install_x,install_y);
        auto [tmpx,tmpy] = p->GetPos();
        p->SetVal(val);
        Insert(p);
        std::cout << "set:" << install_x << " " << install_y << std::endl;
        std::cout << "set:" << tmpx << " " << tmpy << std::endl;
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


#endif  // _VisualList_H_
