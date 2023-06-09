/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 13:49
*******************************************************************************/

#ifndef _GRAPHICSITEM_H_
#define _GRAPHICSITEM_H_
#include "../Logs/Log.h"

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

    // 圆形
    void SetPos(int pos_x,int pos_y,int r) {
        SetPos(pos_x,pos_y,r,r);
    }

    // 修改宽高之后会以原有坐标为中心进行绘制
    void SetWH(int w,int h) {
        _points[2] = w;
        _points[3] = h;
        SetPos(_points[0],_points[1],_points[2],_points[3]);
    }
    // 修改坐标后，以新坐标为中心，原有宽高进行绘制
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
    // TODO ,int ==> T
    void SetVal(int val) {
        _val = val;
    }

    // 返回Item的中心坐标,TODO 对于圆形来说该位置是正确的，但是对于矩形来说，该位置是左上角
    std::tuple<int,int> GetPos() {
        if (_item_type == Rect) {
            return {_points[0]+_points[2]/2,_points[1]+_points[3]/2};
        }
        else if (_item_type == Ellipse) {
            return {_points[0],_points[1]};
        }
    }
    std::tuple<int,int> GetWH() {
        return {_points[2],_points[3]};
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
        painter->drawText(boundingRect(), Qt::AlignCenter, std::to_string(_val).c_str());
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        QGraphicsItem::mousePressEvent(event);
        event->accept();
        emit Selected(this);
    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
        QGraphicsItem::mouseMoveEvent(event);
        event->accept();

        std::cout << "移动" << std::endl;
        emit Move(this);
    }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
        std::cout << "双击" << std::endl;


        // 创建一个QLineEdit小部件
        QLineEdit *lineEdit = new QLineEdit(nullptr);
        lineEdit->setGeometry(QRect(0, 0, 100, 20));  // 设置小部件的位置和大小

        // 设置小部件的属性，例如字体、对齐方式等

        // 将小部件添加到场景中
        scene()->addWidget(lineEdit);

        // 将小部件放置在图形项的中心位置
        QPointF centerPos = mapToScene(boundingRect().center());
        lineEdit->move(centerPos.x() - lineEdit->width() / 2, centerPos.y() - lineEdit->height() / 2);

        // 将光标设置为小部件的焦点
        lineEdit->setFocus();

        QObject::connect(lineEdit,&QLineEdit::editingFinished,[=]{
            int val = std::stoi(lineEdit->text().toStdString());
            SetVal(val);
            lineEdit->deleteLater();
        });

        QGraphicsItem::mouseDoubleClickEvent(event);
    }

signals:
    void Move(GraphicsItem *item);
    void Selected(GraphicsItem *item);

private:
    ItemType _item_type;
    std::vector<int> _points;
    int _val;   // TODO ,仅为数字类型,之后尝试是否为改为T
};
#endif // _GRAPHICSITEM_H_
