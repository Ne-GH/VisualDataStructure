/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/08/18 17:02
*******************************************************************************/


#ifndef VISUALQUEUE_HPP
#define VISUALQUEUE_HPP

#include "VisualStructureBase.hpp"
#include "GraphicsItem.h"
#include "GraphicsScene.h"

#include "Queue.hpp"
#include <array>
#include <vector>

class VisualQueue : public QObject, public VisualStructureBase<MSTL::Queue<GraphicsItem *>>{
Q_OBJECT

private:
    GraphicsScene *_scene;
    int _x = 0;
    int _y = 0;
public:
    VisualQueue() = default;
    ~VisualQueue() = default;
    VisualQueue(GraphicsScene *scene) : _scene(scene) {
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
        for (int i = 1;i < _val.Size(); ++i) {
            auto [x,y] = _val[i-1]->GetPos();
            auto [w,h] = _val[i-1]->GetWH();
            _val[i]->SetPos(x+w,y);
        }
        _scene->update();
    }

    /*******************************************************************************
     * 虚假的删除Delete,真正的删除Remove
     * Queue仅需删除第一个元素即可,应当忽略此处的参数
    *******************************************************************************/
    void Remove(QGraphicsItem *item) {
        auto remove_item = _val.Pop();
        _scene->removeItem(remove_item);
        delete remove_item;

//        ReMove();
    }
    void Insert(GraphicsItem* item) {
        QObject::connect(item,&GraphicsItem::LeftSelected,[=,this](auto pitem){
            for (auto it : _val) {
                it->setSelected(true);
            }
//            std::cout << _val.size() << std::endl;
//            std::cout << x << std::endl;
        });
        QObject::connect(item,&GraphicsItem::RightSelected,[=,this](auto pitem){
            Remove(pitem);
        });
        _scene->addItem(item);
        this->_val.Push(item);
        item->InputVal();

    }
    void Insert(int val) {
        auto p = new GraphicsItem(0,0,100,100);
        int install_x,install_y;
        if (_val.Size() == 0) {
            install_x = _x;
            install_y = _y;
        }
        else {
            std::tie(install_x,install_y) = _val[_val.Size()-1]->GetPos();
            auto [w,h] = _val[_val.Size()-1]->GetWH();
            install_x += w;
        }

        p->SetPos(install_x,install_y);
        p->SetVal(val);
        Insert(p);
    }

    void Delete(GraphicsItem* item) {
//        for (auto it = _val.begin();it != _val.end(); ) {
//            if (*it == item) {
//                it = _val.Delete(it);
//            }
//            else {
//                ++it;
//            }
//        }
    }

    void Draw(GraphicsScene* scene) {  }
    void Updata(GraphicsItem*) {  }
    GraphicsItem* Search(GraphicsItem* item) {  }
};



#endif // VISUALQUEUE_HPP
