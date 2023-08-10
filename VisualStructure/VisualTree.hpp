/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/27 23:38
*******************************************************************************/


#ifndef VISUALTREE_H
#define VISUALTREE_H


#include "VisualStructureBase.hpp"
#include "GraphicsItem.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "ArrowItem.h"

#include "BinaryTree.hpp"
#include <set>


/*******************************************************************************
 * 使用构造函数传入一个Graphics *,之后即可使用 == 来判断连线是否相等
*******************************************************************************/
struct TreeLine {
    GraphicsItem *beg = nullptr;
    GraphicsItem *end = nullptr;
    ArrowItem *line = nullptr;

    TreeLine(GraphicsItem *beg_item = nullptr,GraphicsItem *end_item = nullptr,ArrowItem *arrow = nullptr) :
        beg(beg_item),end(end_item) ,line(arrow) {  }
    //
    bool operator == (const TreeLine &right) const {
        return beg == right.beg || beg == right.end;
    }
    //
    bool operator < (const TreeLine &right) const {
        return this->beg < right.beg;
    }
};

class VisualTree : public QObject, public VisualStructureBase<MSTL::BinaryTree<GraphicsItem *>> {
Q_OBJECT
private:
    GraphicsScene *_scene;
    std::multiset<TreeLine> _lines;

    int _x = 0;
    int _y = 0;

public:
    VisualTree() = default;
    ~VisualTree() = default;
    VisualTree(GraphicsScene *scene) : _scene(scene) {
        int scene_width = _scene->width();
        int scene_height = _scene->height();

        _y = scene_height * 0.3;
        _x = scene_width / 2;
    }


    void AddLine(GraphicsItem *pre,GraphicsItem *back) {

    }
    void RemoveLine(int pos) {


    }
    void Clear(GraphicsScene* scene) {
        scene->clear();
    }


    void Remove(QGraphicsItem* item) {
        _scene->removeItem(item);
        auto node = MSTL::TreeNode<GraphicsItem *>(dynamic_cast<GraphicsItem *>(item));
        _val.Delete(&node);
    }

    void Insert(GraphicsItem* item) {

        QObject::connect(item,&GraphicsItem::RightSelected,[&](auto pitem){
            Delete(pitem);
        });
        _scene->addItem(item);
        item->InputVal();
        QObject::connect(item,&GraphicsItem::InputFish,[=] () mutable {
            auto p = this->_val.Insert(item);
            if (p->_parent == nullptr)
                return;
            auto arrow = new ArrowItem(p->_parent->_val,item);
            auto line = TreeLine(p->_parent->_val,item,arrow);
            _lines.insert(line);
            _scene->addItem(arrow);


//            static int flag = false;
//            if (flag == true) {
//                auto arrow = new ArrowItem(p->_parent->_val,item);
//                _scene->addItem(arrow);
//            }
//            else {
//                flag = true;
//            }
        });

//        this->_val.push_back(item);
    }
    void Insert(int val) {
        auto p = new GraphicsItem(0,0,100,100,GraphicsItem::Ellipse);
        QPointF pos = _scene->views().at(0)->mapToScene(QCursor::pos());

        p->SetPos(pos.x(),pos.y()-50);
        Insert(p);
//
//        // 绘制线条至少需要存在两个元素
//        if (_val.size() < 2) {
//            return;
//        }
//        AddLine(_val[_val.size()-2],_val[_val.size()-1]);

    }

    void Delete(GraphicsItem* item) {
//        for (auto it = _val.begin();it != _val.end(); ) {
//            if (*it == item) {
//                it = _val.erase(it);
//            }
//            else {
//                it ++;
//            }
//        }
//        delete item;
    }

    void Draw(GraphicsScene* scene) {  }
    void Updata(GraphicsItem*) {  }
    GraphicsItem* Search(GraphicsItem* item) {  }
};


#endif




