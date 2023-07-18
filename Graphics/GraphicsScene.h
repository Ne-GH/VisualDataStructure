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
signals:
    void MenuAdd();
private:
    QRectF selectionRect_;
    bool _showRect = false;
protected:
//     重写contextMenuEvent函数处理右键菜单事件
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override {
        QMenu menu;
        // 在菜单中添加所需的操作项
        QAction* action1 = menu.addAction("添加");
        QAction* action2 = menu.addAction("删除");
        // 显示菜单，并获取所选操作项
        QAction* selectedItem = menu.exec(event->screenPos());
        // 处理所选操作项的逻辑
        if (selectedItem == action1) {
            emit MenuAdd();
        }
        else if (selectedItem == action2) {
            // 菜单2
        }
    }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override {
        selectionRect_.setTopLeft(event->scenePos());
        selectionRect_.setSize(QSizeF());
        _showRect = true;

    }
//    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
//    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override {
//        selectionRect_.setTopLeft(event->scenePos());
//        selectionRect_.setSize(QSizeF());
        if (event->buttons() & Qt::LeftButton) {
            if (_showRect == true) {
                QPointF currentPos = event->scenePos();
                selectionRect_.setBottomRight(currentPos);
            }
            update();
        }

        QGraphicsScene::mouseMoveEvent(event);

    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            // 遍历场景中的项并检查是否与选择矩形相交
            QList<QGraphicsItem*> itemsInRect = items(selectionRect_);
            for (QGraphicsItem* item : itemsInRect) {
                item->setSelected(true);
                _showRect = false;
            }
            selectionRect_ = QRectF();
            update();
        }
        QGraphicsScene::mouseReleaseEvent(event);
    }

    void drawBackground(QPainter* painter, const QRectF& rect) override {
        QGraphicsScene::drawBackground(painter, rect);

        // 绘制选择矩形
        if (!selectionRect_.isNull()) {
            painter->setPen(QPen(Qt::blue));
            painter->setBrush(QBrush(Qt::blue, static_cast<Qt::BrushStyle>(Qt::transparent)));
            painter->drawRect(selectionRect_);
        }
    }
public:
    GraphicsScene() {
        setSceneRect(0,0,800,600);
    }
};


#endif // _GRAPHICSSCENE_H_
