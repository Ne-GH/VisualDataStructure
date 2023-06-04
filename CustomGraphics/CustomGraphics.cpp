/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 23:15
*******************************************************************************/
#include <iostream>

#include "CustomGraphics.h"
// 自定义 Item
CustomItem::CustomItem(QGraphicsItem *parent)
        : QGraphicsRectItem(parent)
{
    // 画笔 - 边框色
    QPen p = pen();
    p.setWidth(1);
    p.setColor(QColor(0, 160, 230));

    setPen(p);
    // 画刷 - 背景色
    setBrush(QColor(247, 160, 57));

    // 可选择、可移动
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
}


void CustomItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() == Qt::ShiftModifier) {
            qDebug() << "Custom item left clicked with shift key.";
            // 选中 item
            setSelected(true);
        } else if (event->modifiers() == Qt::AltModifier) {
            qDebug() << "Custom item left clicked with alt key.";
            // 重置 item 大小
            double radius = boundingRect().width() / 2.0;
            QPointF topLeft = boundingRect().topLeft();
            m_centerPointF = QPointF(topLeft.x() + pos().x() + radius, topLeft.y() + pos().y() + radius);
            QPointF pos = event->scenePos();
            qDebug() << boundingRect() << radius << this->pos() << pos << event->pos();
            double dist = sqrt(pow(m_centerPointF.x()-pos.x(), 2) + pow(m_centerPointF.y()-pos.y(), 2));
            if (dist / radius > 0.8) {
                qDebug() << dist << radius << dist / radius;
                m_bResizing = true;
            } else {
                m_bResizing = false;
            }
        } else {
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            event->accept();
        }
    } else if (event->button() == Qt::RightButton) {
        qDebug() << "Custom item right clicked.";
        event->ignore();
    }
}

void CustomItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
        QPointF pos = event->scenePos();
        double dist = sqrt(pow(m_centerPointF.x()-pos.x(), 2) + pow(m_centerPointF.y()-pos.y(), 2));
        setRect(m_centerPointF.x()-this->pos().x()-dist, m_centerPointF.y()-this->pos().y()-dist, dist*2, dist*2);
    } else if(event->modifiers() != Qt::AltModifier) {
        qDebug() << "Custom item moved.";
        QGraphicsItem::mouseMoveEvent(event);
        qDebug() << "moved" << pos();
    }
}

void CustomItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
        m_bResizing = false;
    } else {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

int CustomItem::type() const
{
    return UserType + 1;
}

// 自定义 Scene
void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Custom scene clicked.";
    QGraphicsScene::mousePressEvent(event);
    if (!event->isAccepted()) {
        if (event->button() == Qt::LeftButton) {
            // 在 Scene 上添加一个自定义 item
            QPointF point = event->scenePos();
            CustomItem *item = new CustomItem();
            item->setRect(point.x()-25, point.y()-25, 60, 60);
            addItem(item);
        } else if (event->button() == Qt::RightButton) {
            // 检测光标下是否有 item
            QGraphicsItem *itemToRemove = NULL;
                    foreach (QGraphicsItem *item, items(event->scenePos())) {
                    if (item->type() == QGraphicsItem::UserType+1) {
                        itemToRemove = item;
                        break;
                    }
                }
            // 从 Scene 上移除 item
            if (itemToRemove != NULL)
                removeItem(itemToRemove);
        }
    }
}
void CustomScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    QMenu menu;
    // 在菜单中添加所需的操作项
    QAction* action1 = menu.addAction("添加");
    QAction* action2 = menu.addAction("删除");
    // ...

    // 显示菜单，并获取所选操作项
    QAction* selectedItem = menu.exec(event->screenPos());

    // 处理所选操作项的逻辑
    if (selectedItem == action1) {
        std::cout << "菜单1" << std::endl;

    }
    else if (selectedItem == action2) {

        std::cout << "菜单2" << std::endl;
    // 执行Action 2的操作
    }
    // ...
}

//void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
//    qDebug() << "Custom scene moved.";
//    QGraphicsScene::mouseMoveEvent(event);
//}
//
//void CustomScene::keyPressEvent(QKeyEvent *event) {
//    if (event->key() == Qt::Key_Backspace) {
//        // 移除所有选中的 items
//        qDebug() << "selected items " << selectedItems().size();
//        while (!selectedItems().isEmpty()) {
//            removeItem(selectedItems().front());
//        }
//    } else {
//        QGraphicsScene::keyPressEvent(event);
//    }
//}