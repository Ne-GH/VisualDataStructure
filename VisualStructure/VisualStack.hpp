/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/08/18 16:56
*******************************************************************************/


#ifndef VISUALSTACK_HPP
#define VISUALSTACK_HPP

#include "VisualStructureBase.hpp"
#include "GraphicsItem.h"
#include "GraphicsScene.h"

#include "Stack.hpp"
#include <array>
#include <vector>

class VisualStack : public QObject, public VisualStructureBase<MSTL::Stack<GraphicsItem *>>{
Q_OBJECT

private:
    GraphicsScene *_scene;
    int _x = 0;
    int _y = 0;
public:
    VisualStack() = default;
    ~VisualStack() = default;
    VisualStack(GraphicsScene *scene) : _scene(scene) {
        int scene_width = _scene->width();
        int scene_height = _scene->height();

        _y = scene_height * 0.3;
        _x = scene_width / 2;
    }


    void Clear(GraphicsScene* scene) {
        scene->clear();
    }

    // pos是删除元素的下标
    void ReMove() {
        for (int i = 1;i < val_.Size(); ++i) {
            auto [x,y] = val_[i-1]->GetPos();
            auto [w,h] = val_[i-1]->GetWH();
            val_[i]->SetPos(x+w,y);
        }
        _scene->update();
    }

    /*******************************************************************************
     * 虚假的删除Delete,真正的删除Remove
     * Stack,删除的时候只需要删除最后一个元素即可,无需处理参数以及其余元素
    *******************************************************************************/
    void Remove(QGraphicsItem *item) {
        auto remove_item = val_.Pop();

        _scene->removeItem(remove_item);
        delete remove_item;

//        for (auto p : val_) {
//            auto [x,y] = p->GetPos();
//            std::cout << x << " " << y << std::endl;
//        }
//        std::cout << std::endl;
//        ReMove();
    }
    // 插入 TODO
    void Insert(GraphicsItem* item) {
        QObject::connect(item,&GraphicsItem::LeftSelected,[=,this](auto pitem){
            for (auto it : val_) {
                it->setSelected(true);
            }
//            std::cout << val_.size() << std::endl;
//            std::cout << x << std::endl;
        });
        QObject::connect(item,&GraphicsItem::RightSelected,[=,this](auto pitem){
            Remove(pitem);
        });
        _scene->addItem(item);
        this->val_.Push(item);
        item->InputVal();

    }
    void Insert(int val) {
        auto p = new GraphicsItem(0,0,100,100);
        int install_x,install_y;
        if (val_.Size() == 0) {
            install_x = _x;
            install_y = _y;
        }
        else {
            std::tie(install_x,install_y) = val_[val_.Size()-1]->GetPos();
            auto [w,h] = val_[val_.Size()-1]->GetWH();
            install_x += w;
        }

        p->SetPos(install_x,install_y);
        p->SetVal(val);
        Insert(p);
    }
    // 删除 TODO
    void Delete(GraphicsItem* item) {

//        for (auto it = val_.begin();it != val_.end(); ) {
//            if (*it == item) {
//                it = val_.Delete(it);
//            }
//            else {
//                ++it;
//            }
//        }
    }

    void Draw(GraphicsScene* scene) {  }
    void Updata(GraphicsItem*) {  }
    GraphicsItem* Search(GraphicsItem* item) { return nullptr; }
};


#endif  // VISUALSTACK_H
