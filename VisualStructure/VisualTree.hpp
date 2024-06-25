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
    void RemoveAllArrow() {
        for (auto tmp : _lines) {
            _scene->removeItem(tmp.line);
            delete tmp.line;
        }
        _lines.clear();
    }
    void CreateAllArrow() {
        for (auto node : val_) {
            if (node->parent_) {
                auto arrow = new ArrowItem(node->parent_->val_,node->val_);
                _scene->addItem(arrow);
                _lines.push_back(TreeLine(node->parent_->val_,node->val_,arrow));
                std::cout << node->val_->GetVal() << " " << node->parent_->val_->GetVal() << std::endl;
            }
//
//            if (node->left_) {
//                auto arrow = new ArrowItem(node->val_,node->left_->val_);
//                _scene->addItem(arrow);
//                _lines.push_back(TreeLine(node->val_,node->left_->val_,arrow));
//            }
//
//            if (node->right_) {
//                auto arrow = new ArrowItem(node->val_,node->right_->val_);
//                _scene->addItem(arrow);
//                _lines.push_back(TreeLine(node->val_,node->right_->val_,arrow));
//            }
        }
    }

    // 对于结点的删除,需要先删除arrow后删除item,因为arrow会访问item
    void Remove(QGraphicsItem* item) {
//        auto line = TreeLine(dynamic_cast<GraphicsItem *>(item));

//        // item 是当前选中的节点,line中仅有beg
//        for (auto it = _lines.begin();it != _lines.end();) {
//            if (line == *it) {
//                _scene->removeItem(it->line);
//                delete it->line;
//                it = _lines.erase(it);
//            }
//            else {
//                it ++;
//            }
//        }

        RemoveAllArrow();
        _scene->removeItem(item);
        auto node = MSTL::TreeNode<GraphicsItem *>(dynamic_cast<GraphicsItem *>(item));
        val_.Delete(&node);
        CreateAllArrow();
        AutoLayout();

    }

    void Insert(GraphicsItem* item) {
        QObject::connect(item,&GraphicsItem::RightSelected,[&](auto pitem){
            Delete(pitem);
        });
        _scene->addItem(item);
        item->InputVal();
        QObject::connect(item,&GraphicsItem::InputFish,[=] () mutable {
            RemoveAllArrow();
            auto p = this->val_.Insert(item);
            std::cout << "当前高度: " << val_.GetDeep() << " "
                      <<   "当前宽度: " << val_.GetWidth() << std::endl;
            // 只有root ,无需绘制arrow
            if (p->parent_ == nullptr)
                return;

            CreateAllArrow();
//            auto arrow = new ArrowItem(p->parent_->val_,item);
//            auto line = TreeLine(p->parent_->val_,item,arrow);
//            _lines.push_back(line);
//            _scene->addItem(arrow);

            AutoLayout();

        });
    }
    void Insert(int val) {
        auto p = new GraphicsItem(0,0,100,100,GraphicsItem::Ellipse);
        QPointF pos = _scene->views().at(0)->mapToScene(QCursor::pos());

        p->SetPos(pos.x(),pos.y()-50);
        Insert(p);
    }

    void AutoLayout() {
        int deep = val_.GetDeep();
        std::vector<int> widths(deep+1);
        widths[deep] = 50;
        for (int i = deep-1;i > 0; --i) {
            widths[i] = 2 * widths[i+1] ;       // + 2 * 2 * 50;
        }
        _AutoLayout(val_.GetRoot(),100,100,widths,1);
    }

    void Delete(GraphicsItem* item) override { }
    void Draw(GraphicsScene* scene) {  }
    void Updata(GraphicsItem*) {  }
    GraphicsItem* Search(GraphicsItem* item) { return nullptr; }

private:
    void _AutoLayout(MSTL::TreeNode<GraphicsItem *>*root,int x,int y,std::vector<int> &widths,int deep) {
        if (root == nullptr) {
            return;
        }
        root->val_->SetPos(x,y);
        if (root->left_) {
            _AutoLayout(root->left_,x - widths[deep], y + 100*deep,widths,deep+1);
        }
        if (root->right_) {
            _AutoLayout(root->right_,x + widths[deep],y + 100*deep,widths,deep+1);
        }
    }
};




#endif




