/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/03 00:51
*******************************************************************************/


#ifndef VISUAL_LIST_HPP
#define VISUAL_LIST_HPP

#include "VisualStructureBase.hpp"
#include "GraphicsItem.h"
#include "GraphicsScene.h"
#include "GraphicsView.h"

#include <ArrowItem.h>
#include <vector>
#include <QPoint>

class VisualList : public QObject, public VisualStructureBase<std::vector<GraphicsItem *>> {
    Q_OBJECT
private:
    GraphicsScene *_scene;
    int _x = 0;
    int _y = 0;
    std::vector<ArrowItem *> _lines;

public:
    VisualList() = default;
    ~VisualList() = default;
    VisualList(GraphicsScene *scene) : _scene(scene) {
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
        else if (pos == val_.size()-1) {
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

            auto line = new ArrowItem(val_[pos-1],val_[pos+1]);
            _scene->addItem(line);
            _lines.insert(std::next(_lines.begin(),pos-1),line);
        }

    }

    void Clear(GraphicsScene* scene) {
        scene->clear();
    }


    void Remove(QGraphicsItem* item) {

        int pos = 0;
        while (pos < val_.size()) {
            if (val_[pos] == item) {
                break;
            }
            ++ pos;
        }
        // std::advance(it,pos);
        RemoveLine(pos);
        val_.erase(std::next(val_.begin(),pos));

        _scene->removeItem(item);
        delete item;
    }

    void Insert(GraphicsItem* item) {

        QObject::connect(item,&GraphicsItem::RightSelected,[&](auto pitem){
            Delete(pitem);
        });
        _scene->addItem(item);
        this->val_.push_back(item);
        item->InputVal();
    }
    void Insert(int val) {
        auto p = new GraphicsItem(0,0,100,100,GraphicsItem::Ellipse);

        QPointF pos = _scene->views().at(0)->mapToScene(QCursor::pos());

        p->SetPos(pos.x(),pos.y()-50);
        p->SetVal(val);
        Insert(p);

        // 绘制线条至少需要存在两个元素
        if (val_.size() < 2) {
            return;
        }
        AddLine(val_[val_.size()-2],val_[val_.size()-1]);

    }

    void Delete(GraphicsItem* item) {
        for (auto it = val_.begin();it != val_.end(); ) {
            if (*it == item) {
                it = val_.erase(it);
            }
            else {
                it ++;
            }
        }
        delete item;
    }

    void Draw(GraphicsScene* scene) {  }
    void Updata(GraphicsItem*) {  }
    GraphicsItem* Search(GraphicsItem* item) { return nullptr; }
};


#endif  // _VisualList_H_
