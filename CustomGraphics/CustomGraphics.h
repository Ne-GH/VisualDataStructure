/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 23:15
*******************************************************************************/

#ifndef _GraphicsView_H_
#define _GraphicsView_H_


#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QMenu>
#include <QContextMenuEvent>
#include <QGraphicsSceneContextMenuEvent>

//QGraphicsScene管理QGraphicsItem（单击/选择/移动/缩放/删除）
// 自定义 Item
class CustomItem : public QGraphicsRectItem {
    QList<QGraphicsLineItem *> connectedLines;
public:
    explicit CustomItem(QGraphicsItem *parent = 0);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override {
        // 自定义选中时的边框样式
        if (option->state & QStyle::State_Selected) {
            QPen pen(Qt::black);
            pen.setWidth(2);  // 设置线条宽度
            pen.setStyle(Qt::DashLine);

            // pen.setStyle(Qt::CustomDashLine);  // 设置线条样式为自定义虚线
            // 设置自定义虚线模式，例如让每个线段之间有较大的间隔
            // pen.setDashPattern({4, 8, 4, 8});

            painter->setPen(pen);
        } else {
            // 恢复默认的边框样式
            painter->setPen(QPen(Qt::black, 1));
        }

        // 绘制矩形
        painter->setBrush(QColorConstants::Svg::orange);
        painter->drawRect(rect());
    }

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) {
        if (change == QGraphicsItem::ItemPositionChange && scene()) {
            QPointF new_pos = value.toPointF();
            qDebug() << new_pos << Qt::endl;
            updateConnectedLines(new_pos);
        }
        return QGraphicsRectItem::itemChange(change, value);
    }

    void updateConnectedLines(const QPointF &newPos) {
            foreach (QGraphicsLineItem *line, connectedLines) {
                QLineF currentLine = line->line();
                QPointF startPoint = currentLine.p1();
                QPointF endPoint = currentLine.p2();

                // 根据图形的中心点和线段的起点坐标，计算新的线段
                QLineF newLine(newPos, endPoint + (newPos - startPoint));
                line->setLine(newLine);
            }
    }

    void addConnectedLine(QGraphicsLineItem *line) {
        connectedLines.append(line);
    }
protected:


    // Shift+左键：进行选择  Alt：准备缩放
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    // Alt+拖拽：进行缩放  移动
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    // 使item可使用qgraphicsitem_cast
    int type() const;
private:
    QPointF m_centerPointF;
    bool m_bResizing;
};

// 自定义 Scene
class CustomScene : public QGraphicsScene {
protected:
    // 左键：添加item  右键：移除item
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    // Backspace键移除item
//    void keyPressEvent(QKeyEvent *event);

    // 重写contextMenuEvent函数处理右键菜单事件
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override ;

};

#endif // CUSTOM_ITEM_H



