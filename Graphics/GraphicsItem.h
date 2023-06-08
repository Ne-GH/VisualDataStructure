/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 13:49
*******************************************************************************/

#ifndef _GRAPHICSITEM_H_
#define _GRAPHICSITEM_H_
#include "../Logs/Log.h"

#include <QGraphicsItem>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <vector>

class GraphicsItem :public QObject ,public QGraphicsItem {
    Q_OBJECT
signals:
    void Move(GraphicsItem *item);
public:

    enum ItemType {
        Rect,
        Ellipse
    };

    GraphicsItem(QGraphicsItem *parent = nullptr) : QGraphicsItem(parent) { // 画笔 - 边框色
        _points.resize(4);
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
    }

    GraphicsItem(int pos_x,int pos_y,int item_w,int item_h,ItemType item_type = Rect) : GraphicsItem(){
        _points[0] = pos_x;
        _points[1] = pos_y;
        _points[2] = item_w;
        _points[3] = item_h;
        _item_type = item_type;
    }

    ~GraphicsItem() {  }

    void SetItemType(ItemType item_type) {
        _item_type = item_type;
    }

    // 矩形
    void SetPos(int pos_x,int pos_y,int item_w,int item_h) {
        _points[0] = pos_x - item_w/2;
        _points[1] = pos_y - item_h/2;
        _points[2] = item_w;
        _points[3] = item_h;
    }
    // 圆形
    void SetPos(int pos_x,int pos_y,int r) {
        SetPos(pos_x,pos_y,r,r);
    }
    void SetWH(int w,int h) {
        _points[2] = w;
        _points[3] = h;
        SetPos(_points[0],_points[1],_points[2],_points[3]);
    }
    void SetPos(int pos_x,int pos_y) {
        if (_item_type == Rect) {
            _points[0] = pos_x - _points[2]/2;
            _points[1] = pos_y - _points[3]/2;
        }
        else if (_item_type == Ellipse) {
            _points[0] = pos_x;
            _points[1] = pos_y;
        }
    }

protected:
    QRectF boundingRect() const override {
        if (_item_type == Rect) {
            return QRectF(_points[0],_points[1],_points[2],_points[3]);
        }
        else if (_item_type == Ellipse){
            return QRectF(_points[0],_points[1],_points[2],_points[3]);
        }
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(Qt::transparent);

        QPen pen(QColor(51, 51, 51));
        pen.setCapStyle(Qt::SquareCap);
        pen.setJoinStyle(Qt::RoundJoin);

        //选中后，图形变成虚线
        if (option->state & QStyle::State_Selected) {
            pen.setStyle(Qt::DashLine); //虚线
        }
        else {
            pen.setStyle(Qt::SolidLine); //实线
        }
        painter->setPen(pen);
        painter->setBrush(QColorConstants::Svg::orange);
        if (_item_type == Rect) {
            painter->drawRect(QRect{_points[0],_points[1],_points[2],_points[3]});
        }
        else if (_item_type == Ellipse){
            painter->drawEllipse(boundingRect());
        }
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        QGraphicsItem::mousePressEvent(event);
        event->accept();
        emit Move(this);
    }

private:
    ItemType _item_type;
    std::vector<int> _points;
};
#endif // _GRAPHICSITEM_H_
