/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 15:11
*******************************************************************************/

#include <iostream>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Logs/Log.h"

#include "CustomGraphics/CustomGraphics.h"

MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent),
                        ui(new Ui::MainWindow){
    ui->setupUi(this);
    LOG.AddLog("MainWindow构造函数");
    auto log_action = new QAction("日志");
    ui->menu_bar->addAction(log_action);
    connect(log_action,&QAction::triggered,[=]{
        LOG.Show();
    });

    // 创建 QGraphicsView 和 QGraphicsScene 对象
    QGraphicsView *graphicsView = new QGraphicsView(this);
    QGraphicsScene *scene = new CustomScene();

    // 设置 QGraphicsView 铺满窗口的中心部分
    setCentralWidget(graphicsView);

//    QRectF rect(10, 10, 100, 100);  // 指定矩形的位置和尺寸
    auto rect_item = new CustomItem();
//    rect_item->setRect(rect);

    scene->addItem(rect_item);  // 将矩形项添加到场景中

    // 将 QGraphicsScene 设置给 QGraphicsView
    graphicsView->setScene(scene);

    LOG.AddLog("MainWindow构造完成");
}
