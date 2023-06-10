/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 15:11
*******************************************************************************/

#include <iostream>
#include <QGraphicsView>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Logs/Log.h"

#include "Graphics/GraphicsScene.h"
#include "Graphics/GraphicsItem.h"
#include "Graphics/GraphicsView.h"
#include "Structure/Array.hpp"

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
    GraphicsView *graphicsView = new GraphicsView(this);
    graphicsView->setAlignment(Qt::AlignCenter);
    setCentralWidget(graphicsView);
    auto scene = new GraphicsScene();
    graphicsView->setScene(scene);
//    graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatioByExpanding);
//    view->scale(scaleFactor, scaleFactor);

    auto a = new Array(scene);

    QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
        a->Insert(0);
    });

    LOG.AddLog("MainWindow构造完成");
    LOG.AddLog("启动完成");
    ui->status_bar->showMessage("启动完成...");
}

