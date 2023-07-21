/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 13:49
*******************************************************************************/

#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H
#include "Setting.h"

#include <vector>
#include <iostream>
#include <QLineEdit>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyle>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>


class GraphicsItem :public QObject ,public QGraphicsItem {
    Q_OBJECT
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
    GraphicsItem(int val) : GraphicsItem() {
        SetVal(val);
    }

    GraphicsItem(int pos_x,int pos_y,int item_w,int item_h,ItemType item_type = Rect) : GraphicsItem(){
        _points.resize(4);
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
    // 以新坐标为中心，新宽高进行绘制
    void SetPos(int pos_x,int pos_y,int item_w,int item_h) {
        _points[0] = pos_x - item_w/2;
        _points[1] = pos_y - item_h/2;
        _points[2] = item_w;
        _points[3] = item_h;
    }


    // 修改宽高之后会以原有坐标为中心进行绘制
    void SetWH(int w,int h) {
        _points[2] = w;
        _points[3] = h;
        SetPos(_points[0],_points[1],_points[2],_points[3]);
    }
    // 修改坐标后，以新坐标为中心，原有宽高进行绘制
    void SetPos(int pos_x,int pos_y) {
        setPos(QPointF(pos_x - _points[2]/2,pos_y - _points[3]/2));
    }
    // TODO ,int ==> T
    void SetVal(int val) {
        _val = val;
    }
    void InputVal() {
        QLineEdit *lineEdit = new QLineEdit(nullptr);
        lineEdit->setGeometry(QRect(0, 0, 30, 25));

        scene()->addWidget(lineEdit);
        QPointF centerPos = mapToScene(boundingRect().center());
        lineEdit->move(centerPos.x() - lineEdit->width() / 2, centerPos.y() - lineEdit->height() / 2);
        // 将光标设置为小部件的焦点
        lineEdit->setFocus();
        QObject::connect(lineEdit,&QLineEdit::editingFinished,[=,this]{
            try {
                int val = std::stoi(lineEdit->text().toStdString());
                SetVal(val);
                lineEdit->deleteLater();
            }
            catch (...) {
                lineEdit->deleteLater();
                InputVal();
            }
        });
    }
    // 返回Item的中心坐标
    std::tuple<int,int> GetPos() {
//      return {_points[0]+_points[2]/2,_points[1]+_points[3]/2};
        QPointF scene_pos = this->scenePos() + boundingRect().center();
        int x =  scene_pos.x();
        int y =  scene_pos.y();
        return {x,y};
    }
    // 返回Item的宽高
    std::tuple<int,int> GetWH() {
        return {_points[2],_points[3]};
    }
protected:
    QRectF boundingRect() const override {
        return QRectF(_points[0],_points[1],_points[2],_points[3]);
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
        QColor color = "#00aaff";
        painter->setBrush(color);
        if (_item_type == Rect) {
            painter->drawRect(QRectF(_points[0],_points[1],_points[2],_points[3]));
        }
        else if (_item_type == Ellipse){
            painter->drawEllipse(boundingRect());
        }
        painter->drawText(boundingRect(), Qt::AlignCenter, std::to_string(_val).c_str());
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            emit LeftSelected(this);
        }
        else if (event->button() == Qt::RightButton) {
//            emit RightSelected(this);
        }
        QGraphicsItem::mousePressEvent(event);
        event->accept();
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
        QGraphicsItem::mouseReleaseEvent(event);
        event->accept();
    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
        emit Move(this);
        QGraphicsItem::mouseMoveEvent(event);
        event->accept();
    }

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
        InputVal();
        QGraphicsItem::mouseDoubleClickEvent(event);
    }

signals:
    void Move(GraphicsItem *item);
    void LeftSelected(GraphicsItem *item);
    void RightSelected(GraphicsItem *item);

private:
    ItemType _item_type;
    std::vector<int> _points;
    int _val;   // TODO ,仅为数字类型,之后尝试是否为改为T
};
#endif // _GRAPHICSITEM_H_
