/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/10 21:50
*******************************************************************************/

#ifndef _GraphicsView_H_
#define _GraphicsView_H_

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QScrollBar>
class GraphicsView : public QGraphicsView {
    int scale_m = 1;
protected:
    GraphicsView() {
        setDragMode(QGraphicsView::NoDrag);//(QGraphicsView::RubberBandDrag);//QGraphicsView::ScrollHandDrag
        scale_m = 1;//图形原始比例
        setStyleSheet("padding: 0px; border: 0px;");//无边框
        setMouseTracking(true);//跟踪鼠标位置
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏水平条
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖条
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    }

    void wheelEvent(QWheelEvent *event) {

        // 获取当前鼠标相对于view的位置;
        QPointF cursorPoint = event->position();
        // 获取当前鼠标相对于scene的位置;
        QPointF scenePos = this->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));

        // 获取view的宽高;
        qreal viewWidth = this->viewport()->width();
        qreal viewHeight = this->viewport()->height();

        // 获取当前鼠标位置相当于view大小的横纵比例;
        qreal hScale = cursorPoint.x() / viewWidth;
        qreal vScale = cursorPoint.y() / viewHeight;

        // 当前放缩倍数;
        qreal scaleFactor = this->transform().m11();
        int wheelDeltaValue = event->angleDelta().y();
        // 向上滚动，放大;
        if (wheelDeltaValue > 0) {
            this->scale(1.2, 1.2);
        }
            // 向下滚动，缩小;
        else {
            this->scale(1.0 / 1.2, 1.0 / 1.2);
        }

        // 将scene坐标转换为放大缩小后的坐标;
        QPointF viewPoint = this->transform().map(scenePos);
        // 通过滚动条控制view放大缩小后的展示scene的位置;
        horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
        verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));

    }



public:
    GraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {
        setDragMode(QGraphicsView::ScrollHandDrag);
        scale_m = 1;//图形原始比例
        setStyleSheet("padding: 0px; border: 0px;");//无边框
        setMouseTracking(true);//跟踪鼠标位置
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏水平条
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖条
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    }

};


#endif // _GraphicsView_H_
