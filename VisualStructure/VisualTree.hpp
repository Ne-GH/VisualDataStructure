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

#include <vector>
#include <QPoint>

class VisualTree : public QObject, public VisualStructureBase<std::vector> {
Q_OBJECT
private:
    GraphicsScene *_scene;
    int _x = 0;
    int _y = 0;
    using VisualStructureBase<std::vector>::_val;
    std::vector<ArrowItem *> _lines;

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
        auto line = new ArrowItem(pre,back);
        _lines.push_back(line);
        _scene->addItem(line);
    }
    void RemoveLine(int pos) {

        // line :
        // 0       1       2       3       4
        // 0 1     1 2     2 3     3 4
        if (_lines.size() == 0)
            return ;
        if (pos == 0) {
            _scene->removeItem(*_lines.begin());
            delete _lines[0];
            _lines.erase(_lines.begin());
        }
        else if (pos == _val.size()-1) {
            _scene->removeItem(*(_lines.end()-1));
            delete _lines[pos-1];
            _lines.erase(_lines.end()-1);
        }
        else {
            _scene->removeItem(*(std::next(_lines.begin(),pos-1)));
            delete _lines[pos-1];
            _lines.erase(std::next(_lines.begin(),pos-1));
            _scene->removeItem(*(std::next(_lines.begin(),pos-1)));
            delete _lines[pos-1];
            _lines.erase(std::next(_lines.begin(),pos-1));

            auto line = new ArrowItem(_val[pos-1],_val[pos+1]);
            _scene->addItem(line);
            _lines.insert(std::next(_lines.begin(),pos-1),line);
        }

    }

    void Clear(GraphicsScene* scene) {
        scene->clear();
    }


    void Remove(QGraphicsItem* item) {

        int pos = 0;
        while (pos < _val.size()) {
            if (_val[pos] == item) {
                break;
            }
            ++ pos;
        }
        // std::advance(it,pos);
        RemoveLine(pos);
        _val.erase(std::next(_val.begin(),pos));

        _scene->removeItem(item);
        delete item;
    }

    void Insert(GraphicsItem* item) {

        QObject::connect(item,&GraphicsItem::RightSelected,[&](auto pitem){
            Delete(pitem);
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
        AddLine(_val[_val.size()-2],_val[_val.size()-1]);

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
        delete item;
    }

    void Draw(GraphicsScene* scene) {  }
    void Updata(GraphicsItem*) {  }
    GraphicsItem* Search(GraphicsItem* item) {  }
};


#endif




