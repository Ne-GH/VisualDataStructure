/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/07/17 01:23
*******************************************************************************/


#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QPen>
#include <QPainter>
#include <QLineF>
#include "GraphicsItem.h"

class ArrowItem : public QGraphicsLineItem {
    GraphicsItem *start_item_;
    GraphicsItem *end_item_;
    QPolygonF arrow_head_;
public:

    //构造函数(两个item参数)
    ArrowItem(GraphicsItem *startI,GraphicsItem *endI,QGraphicsItem *parent = nullptr) {
       end_item_ = startI; //起点item
        start_item_ = endI; //终点item
        this->setZValue(-1); //目的：让箭头后置
        setFlag(QGraphicsItem::ItemIsSelectable);
        setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    }

    //item绘制区域的估计值
    QRectF boundingRect() const override {
        //item绘制区域的估计值
        qreal extra = (this->pen().width() + 20) /2;
        return QRectF(line().p1(),QSizeF(line().p2().x()-line().p1().x(),line().p2().y() - line().p1().y()))
                .normalized().adjusted(-extra,-extra,extra,extra);
    }
    //实际绘制
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)override {

        QPen pen(Qt::black);
        painter->setPen(pen);
        painter->setRenderHint(QPainter::Antialiasing); // 开启抗锯齿

        painter->setBrush(Qt::black);
        constexpr  qreal arrow_size = 10;
        auto [sx,sy] = start_item_->GetPos();
        auto [ex,ey] = end_item_->GetPos();
        QPointF spos(sx,sy),epos(ex,ey);

        QPointF lineStart(spos);
        QPointF lineEnd(epos);

        // 计算直线的斜率和截距
        qreal angles = std::atan2(lineEnd.y() - lineStart.y(), lineEnd.x() - lineStart.x());
        auto tx = cos(angles) * 50;
        auto ty = sin(angles) * 50;

        painter->setPen(Qt::black);
        QPointF t(sx+tx,sy+ty);
        QLineF arrow(t,epos);
        setLine(arrow);

        double angle = std::atan2(-line().dy(),line().dx()); //反正切 [-PI,PI]
        QPointF arrow1 = line().p1() +
                          QPointF(sin(angle + M_PI / 3) * arrow_size, //计算对边
                                  cos(angle + M_PI / 3) * arrow_size); //计算临边
        QPointF arrow2 = line().p1() +
                          QPointF(sin(angle + M_PI - M_PI / 3) * arrow_size,
                                  cos(angle + M_PI - M_PI / 3) * arrow_size);

        arrow_head_.clear();
        arrow_head_ << line().p1() << arrow1 << arrow2;

        painter->drawLine(line());
        painter->drawPolygon(arrow_head_);
    }
    void SetDestination(GraphicsItem * new_dest) {
       end_item_ = new_dest;
    }



};


#endif  // ARROW_H

