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
    resize(850,650);
    LOG.AddLog("MainWindow构造函数");
    auto log_action = new QAction("日志");
    ui->menu_bar->addAction(log_action);
    connect(log_action,&QAction::triggered,[=]{
        LOG.Show();
    });

    // 创建 QGraphicsView 和 QGraphicsScene 对象
    QGraphicsView *graphicsView = new QGraphicsView(this);
    CustomScene *scene = new CustomScene();
    graphicsView->setAlignment(Qt::AlignCenter);
//    graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
//    scene->setSceneRect(-100,-100,100,100);
    // 设置 QGraphicsView 铺满窗口的中心部分
    setCentralWidget(graphicsView);


    Arrary aa(scene);
    auto i1 = new CustomItem(100,100,100,100);
    auto i2 = new CustomItem(200,200,10,10);
    aa.Install(i1);
    aa.Install(i2);


    // 将 QGraphicsScene 设置给 QGraphicsView
    graphicsView->setScene(scene);


    LOG.AddLog("MainWindow构造完成");
}
