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

    // == 只需要left的begin 出现在right的begin或者end上即可
    bool operator == (const TreeLine &right) const {
        if (right.end == nullptr) {
            return right.beg == beg || right.beg == end;
        }
        return beg == right.beg || beg == right.end;
    }
    //
    bool operator < (const TreeLine &right) const {
        return this->beg < right.beg;
    }

    // Equal的比较相较于 == 更为严格,需要beg == beg && end == end
    bool Equal(const TreeLine& other) {
        return beg == other.beg && end == other.end;
    }
};

class VisualTree : public QObject, public VisualStructureBase<MSTL::BinaryTree<GraphicsItem *>> {
Q_OBJECT
private:
    GraphicsScene *_scene;
    std::vector<TreeLine> _lines;

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

    void Clear(GraphicsScene* scene) {
        scene->clear();
    }
    bool FindLine(const TreeLine &line) {
        for (auto _ : _lines) {
            if (_.Equal(line))
                return true;
        }
        return false;
    }

    // 对于结点的删除,需要先删除arrow后删除item,因为arrow会访问item
    void Remove(QGraphicsItem* item) {
        auto line = TreeLine(dynamic_cast<GraphicsItem *>(item));

        // item 是当前选中的节点,line中仅有beg
        for (auto it = _lines.begin();it != _lines.end();) {
            if (line == *it) {
                _scene->removeItem(it->line);
                delete it->line;
                it = _lines.erase(it);
            }
            else {
                it ++;
            }
        }

        _scene->removeItem(item);
        auto node = MSTL::TreeNode<GraphicsItem *>(dynamic_cast<GraphicsItem *>(item));
        _val.Delete(&node);

        for (auto node : _val) {
            if (node->_parent) {
                std::cout << "有父节点" << " ";
            }
            if (node->_modify_flag) {
                std::cout << "(modify)" << " ";
            }
            if (node->_modify_flag == true) {
                if (node->_parent) {
                    if (!FindLine(TreeLine(node->_parent->_val,node->_val))) {
                        auto arrow = new ArrowItem(node->_parent->_val,node->_val);
                        _scene->addItem(arrow);
                        _lines.push_back(TreeLine(node->_parent->_val,node->_val,arrow));
                    }
                }

                if (node->_left) {
                    if (!FindLine(TreeLine(node->_val,node->_left->_val))) {
                        auto arrow = new ArrowItem(node->_val,node->_left->_val);
                        _scene->addItem(arrow);
                        _lines.push_back(TreeLine(node->_val,node->_left->_val,arrow));
                    }
                }

                if (node->_right) {
                    if (!FindLine(TreeLine(node->_val,node->_right->_val))) {
                        auto arrow = new ArrowItem(node->_val,node->_right->_val);
                        _scene->addItem(arrow);
                        _lines.push_back(TreeLine(node->_val,node->_right->_val,arrow));
                    }

                }
            }

        }

    }

    void Insert(GraphicsItem* item) {
        QObject::connect(item,&GraphicsItem::RightSelected,[&](auto pitem){
            Delete(pitem);
        });
        _scene->addItem(item);
        item->InputVal();
        QObject::connect(item,&GraphicsItem::InputFish,[=] () mutable {
            auto p = this->_val.Insert(item);
            std::cout << "当前高度: " << _val.GetDeep() << " "
                      <<   "当前宽度: " << _val.GetWidth() << std::endl;
            if (p->_parent == nullptr)
                return;
            auto arrow = new ArrowItem(p->_parent->_val,item);
            auto line = TreeLine(p->_parent->_val,item,arrow);
            _lines.push_back(line);
            _scene->addItem(arrow);

            int deep = _val.GetDeep();
            std::vector<int> widths(deep+1);
            widths[deep] = 50;
            for (int i = deep-1;i > 0; --i) {
                widths[i] = 2 * widths[i+1] ;// + 2 * 2 * 50;
            }
            AutoLayout(_val.GetRoot(),100,100,widths,1);
        });
    }
    void Insert(int val) {
        auto p = new GraphicsItem(0,0,100,100,GraphicsItem::Ellipse);
        QPointF pos = _scene->views().at(0)->mapToScene(QCursor::pos());

        p->SetPos(pos.x(),pos.y()-50);
        Insert(p);
    }

    void AutoLayout(MSTL::TreeNode<GraphicsItem *>*root,int x,int y,std::vector<int> &widths,int deep) {
        if (root == nullptr) {
            return;
        }
        root->_val->SetPos(x,y);
        if (root->_left) {
            AutoLayout(root->_left,x - widths[deep], y + 100*deep,widths,deep+1);
        }
        if (root->_right) {
            AutoLayout(root->_right,x + widths[deep],y + 100*deep,widths,deep+1);
        }
    }


    void Delete(GraphicsItem* item) override { }
    void Draw(GraphicsScene* scene) {  }
    void Updata(GraphicsItem*) {  }
    GraphicsItem* Search(GraphicsItem* item) {  }
};




#endif




