/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 16:12
*******************************************************************************/

#ifndef VISUAL_ARRAY_HPP
#define VISUAL_ARRAY_HPP

#include "VisualStructureBase.hpp"
#include "GraphicsItem.h"
#include "GraphicsScene.h"

#include "Array.hpp"
#include <array>
#include <vector>




class VisualArray : public QObject, public VisualStructureBase<MSTL::Arrary<GraphicsItem *>>{
    Q_OBJECT

private:
    GraphicsScene *_scene;
    int x_ = 0;
    int y_ = 0;
public:
    VisualArray() = default;
    ~VisualArray() = default;
    VisualArray(GraphicsScene *scene) : _scene(scene) {
        int scene_width = _scene->width();
        int scene_height = _scene->height();

        y_ = scene_height * 0.3;
        x_ = scene_width / 2;
    }


    void Clear(GraphicsScene* scene) {
        scene->clear();
    }

    void Push_back(int val) {
        Insert(val);
    }
    // pos是删除元素的下标
    void ReMove() {
        for (int i = 1;i < val_.size(); ++i) {
            auto [x,y] = val_[i-1]->GetPos();
            auto [w,h] = val_[i-1]->GetWH();
            val_[i]->SetPos(x+w,y);
        }
        _scene->update();
    }
    void Remove(QGraphicsItem *item) {
        for (auto it = val_.begin();it != val_.end(); ++it) {
            if (*it == item) {
                val_.Delete(it);
                break;
            }
        }
        _scene->removeItem(item);
        delete item;

        for (auto p : val_) {
            auto [x,y] = p->GetPos();
            std::cout << x << " " << y << std::endl;
        }
        std::cout << std::endl;
        ReMove();
    }
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
        this->val_.PushBack(item);
        item->InputVal();

    }
    // TODO int => T
    void Insert(int val) {
        auto p = new GraphicsItem(0,0,100,100);
        int installx_,instally_;
        if (val_.size() == 0) {
            installx_ = x_;
            instally_ = y_;
        }
        else {
            std::tie(installx_,instally_) = val_[val_.size()-1]->GetPos();
            auto [w,h] = val_[val_.size()-1]->GetWH();
            installx_ += w;
        }

        p->SetPos(installx_,instally_);
        p->SetVal(val);
        Insert(p);
    }

    void Delete(GraphicsItem* item) {
        for (auto it = val_.begin();it != val_.end(); ) {
            if (*it == item) {
                it = val_.Delete(it);
            }
            else {
                 ++it;
            }
        }
    }

    void Draw(GraphicsScene* scene) {  }
    void Updata(GraphicsItem*) {  }
    GraphicsItem* Search(GraphicsItem* item) { return nullptr; }
};


#endif // _ARRAY_H_
