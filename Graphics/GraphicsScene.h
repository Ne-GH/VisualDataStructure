/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 15:08
*******************************************************************************/

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "GraphicsItem.h"

#include <QGraphicsScene>
#include <QMenu>
#include <QList>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

    QRectF selection_rect_;
    bool show_rect_ = false;
signals:
    void MenuAdd();
    void MenuDel(QGraphicsItem *);

protected:
//     重写contextMenuEvent函数处理右键菜单事件
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override {
        // 获取鼠标当前位置下的 item

        QMenu menu;
        // 在菜单中添加所需的操作项
        QAction* add = menu.addAction("添加");
        // 显示菜单，并获取所选操作项
        QAction* del = nullptr;
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        if (item) {
            std::cout << "右键点击" << std::endl;
            del = menu.addAction("删除");
        }
        QAction* selectedItem = menu.exec(event->screenPos());

        // 处理所选操作项的逻辑
        if (selectedItem == add) {
            emit MenuAdd();
        }
        else if (selectedItem == del) {
            // 菜单2
            emit MenuDel(item);
        }
    }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override {
        selection_rect_.setTopLeft(event->scenePos());
        selection_rect_.setSize(QSizeF());
        show_rect_ = true;
        QGraphicsScene::mousePressEvent(event);

    }
//    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
//    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
//        selection_rect_.setTopLeft(event->scenePos());
//        selection_rect_.setSize(QSizeF());

        if (event->buttons() & Qt::LeftButton) {
            if (show_rect_ == true) {
                QPointF currentPos = event->scenePos();
                selection_rect_.setBottomRight(currentPos);
            }
            update();
        }
//        // 获取鼠标当前位置下的 item
//        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
//
//        // 检查 item 是否存在
//        if (item) {
//            // 比较 item 的当前位置与之前的位置
//            if (item->pos() != item->scenePos()) {
//                // item 移动了
//            }
//        }
        QGraphicsScene::mouseMoveEvent(event);

    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            // 遍历场景中的项并检查是否与选择矩形相交
            QList<QGraphicsItem*> itemsInRect = items(selection_rect_);
            for (QGraphicsItem* item : itemsInRect) {
                item->setSelected(true);
                show_rect_ = false;
            }
            selection_rect_ = QRectF();
            update();
        }
        QGraphicsScene::mouseReleaseEvent(event);
    }

    void drawBackground(QPainter* painter, const QRectF& rect) override {
        QGraphicsScene::drawBackground(painter, rect);

        // 绘制选择矩形
        if (!selection_rect_.isNull()) {
            painter->setPen(QPen(Qt::blue));
            painter->setBrush(QBrush(Qt::blue, static_cast<Qt::BrushStyle>(Qt::transparent)));
            painter->drawRect(selection_rect_);
        }
    }
public:
    GraphicsScene() {
        setSceneRect(0,0,800,600);
    }
};


#endif // _GRAPHICSSCENE_H_
