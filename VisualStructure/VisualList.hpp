/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/03 00:51
*******************************************************************************/


#ifndef _VisualList_H_
#define _VisualList_H_

#include "VisualStructureBase.hpp"
#include "GraphicsItem.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"
#include "Log.h"

#include <vector>
#include <QPoint>

class VisualList : public QObject, public VisualStructureBase<std::vector> {
    Q_OBJECT
private:
    GraphicsScene *_scene;
    int _x = 0;
    int _y = 0;
    using VisualStructureBase<std::vector>::_val;

    std::vector<QLine> _lines;
public:
    VisualList() = default;
    ~VisualList() = default;
    VisualList(GraphicsScene *scene) : _scene(scene) {
            int scene_width = _scene->width();
            int scene_height = _scene->height();

            _y = scene_height * 0.3;
            _x = scene_width / 2;
    }

    void AddLine() {
        if (_val.size() <= 1)
            return;
        int begin_x,begin_y,end_x,end_y;

        for (int i = 0;i < _val.size()-1 ; ++i) {
            std::tie(begin_x,begin_y) = _val[i]->GetPos();
            std::tie(end_x,end_y) = _val[i+1]->GetPos();
//            auto line = new QLine(begin_x,begin_y,end_x,end_y);
            QGraphicsLineItem* line = new QGraphicsLineItem();
            line->setLine(QLineF(begin_x,begin_y, end_x,end_y));
            line->setZValue(-1); // 设置 Z 值为较小的负值
            _scene->addItem(line);
//            _scene->addLine(begin_x,begin_y,end_x,end_y);
        }
    }
    void RemoveLine() {

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
//            for (auto it : _val) {
//                it->setSelected(true);
//            }
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

        QPointF pos = _scene->views().at(0)->mapToScene(QCursor::pos());

        p->SetPos(pos.x(),pos.y()-50);
        p->SetVal(val);
        Insert(p);

        // 绘制线条至少需要存在两个元素
        if (_val.size() < 2) {
            return;
        }

        auto pre = _val[_val.size()-2];
        auto [begin_x,begin_y] = pre->GetPos();
        auto [end_x,end_y] = p->GetPos();
        QGraphicsLineItem* line = new QGraphicsLineItem();
        line->setLine(QLineF(begin_x,begin_y, end_x,end_y));
        line->setZValue(-1);
        _scene->addItem(line);

        QObject::connect(p,&GraphicsItem::Move,[=]{
            auto [begin_x,begin_y] = pre->GetPos();
            auto [end_x,end_y] = p->GetPos();
            line->setLine(QLineF(begin_x,begin_y, end_x,end_y));
        });
        QObject::connect(pre,&GraphicsItem::Move,[=]{
            auto [begin_x,begin_y] = pre->GetPos();
            auto [end_x,end_y] = p->GetPos();
            line->setLine(QLineF(begin_x,begin_y, end_x,end_y));
        });
//        AddLine();
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
