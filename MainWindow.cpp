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
#include "Structure/Arrary.hpp"

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
    CustomScene *scene = new CustomScene();

    // 设置 QGraphicsView 铺满窗口的中心部分
    setCentralWidget(graphicsView);

    QRectF rect(10, 10, 100, 100);  // 指定矩形的位置和尺寸
    auto rect_item = new CustomItem();
    rect_item->setRect(rect);

    QRectF rect2(20, 20, 100, 100);  // 指定矩形的位置和尺寸
    auto rect_item2 = new CustomItem();
    rect_item2->setRect(rect2);
//    scene->addItem(rect_item);  // 将矩形项添加到场景中
    Arrary<CustomItem *> a;
    a.Install(rect_item);
    a.Install(rect_item2);
    a.Draw(scene);




    // 将 QGraphicsScene 设置给 QGraphicsView
    graphicsView->setScene(scene);

//
//    CustomItem *rect1 = new CustomItem();
//    rect1->setRect(0, 0, 100, 100);
//    CustomItem *rect2 = new CustomItem();
//    rect2->setRect(200, 0, 100, 100);
//
//    QGraphicsLineItem *line = new QGraphicsLineItem(rect1->rect().center().x(), rect1->rect().center().y(),
//                                                    rect2->rect().center().x(), rect2->rect().center().y());
//
//    // 将连接线段添加到图形项的 connectedLines 列表中
//    rect1->addConnectedLine(line);
//    rect2->addConnectedLine(line);
//
//    scene->addItem(rect1);
//    scene->addItem(rect2);
//    scene->addItem(line);

    LOG.AddLog("MainWindow构造完成");
}
