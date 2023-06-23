/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 15:11
*******************************************************************************/

#include <iostream>
#include <random>
#include <QTimer>
#include <QThread>
#include <thread>
#include <algorithm>
#include <QGraphicsView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QBarCategoryAxis>
#include <QPalette>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Logs/Log.h"

#include "GraphicsScene.h"
#include "GraphicsItem.h"
#include "GraphicsView.h"
#include "Array.hpp"
#include "Sort.hpp"

MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent),
                        ui(new Ui::MainWindow){
    ui->setupUi(this);



    auto log_action = new QAction("日志");
    ui->menu_bar->addAction(log_action);
    connect(log_action,&QAction::triggered,[=]{
        LOG.Show();
    });

    auto sort_action = new QAction("排序");
    ui->menu_bar->addAction(sort_action);

    auto s = new Sort(this);
    QObject::connect(sort_action,&QAction::triggered,[=]{
        s->begin();
    });

    QObject::connect(s,&Sort::Updata,[=]{
        s->Show(this);
    });






//    LOG.AddLog("MainWindow构造函数");

    // 创建 QGraphicsView 和 QGraphicsScene 对象
//    GraphicsView *graphicsView = new GraphicsView(this);
//    graphicsView->setAlignment(Qt::AlignCenter);
//    setCentralWidget(graphicsView);
//    auto scene = new GraphicsScene();
//    graphicsView->setScene(scene);
////    graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatioByExpanding);
////    view->scale(scaleFactor, scaleFactor);
//
//    auto a = new Array(scene);
//
//    QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
//        a->Insert(0);
//    });








    LOG.AddLog("MainWindow构造完成");
    LOG.AddLog("启动完成");
    ui->status_bar->showMessage("启动完成...");
}

