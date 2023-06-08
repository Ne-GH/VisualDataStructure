/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/08 15:08
*******************************************************************************/

#ifndef _GRAPHICSSCENE_H_
#define _GRAPHICSSCENE_H_

#include <QGraphicsScene>
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>

class GraphicsScene : public QGraphicsScene {
protected:
    // 重写contextMenuEvent函数处理右键菜单事件
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override {
        QMenu menu;
        // 在菜单中添加所需的操作项
        QAction* action1 = menu.addAction("添加");
        QAction* action2 = menu.addAction("删除");
        // 显示菜单，并获取所选操作项
        QAction* selectedItem = menu.exec(event->screenPos());
        // 处理所选操作项的逻辑
        if (selectedItem == action1) {
            // 菜单1
        }
        else if (selectedItem == action2) {
            // 菜单2
        }
    }
public:
    GraphicsScene() {
        setSceneRect(0,0,800,600);
    }
};


#endif // _GRAPHICSSCENE_H_
