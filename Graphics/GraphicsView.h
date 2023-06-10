/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/10 21:50
*******************************************************************************/

#ifndef _GraphicsView_H_
#define _GraphicsView_H_

#include <QGraphicsView>
#include <QWheelEvent>
#include <QScrollBar>
class GraphicsView : public QGraphicsView {
protected:
    void wheelEvent(QWheelEvent *event) {
        // 获取当前的缩放因子
        qreal scaleFactor = pow(2.0, event->angleDelta().y() / 240.0);

        // 获取鼠标相对于视图的位置
        QPointF mousePos = event->position();

        // 平移视图到鼠标位置
        translate(mousePos.x(), mousePos.y());

        // 进行缩放操作
        scale(scaleFactor, scaleFactor);

        // 再次平移视图回原位置
        translate(-mousePos.x(), -mousePos.y());

        // 更新视图
        update();
    }





public:
    GraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {
        setDragMode(QGraphicsView::ScrollHandDrag);
    }

};


#endif // _GraphicsView_H_
