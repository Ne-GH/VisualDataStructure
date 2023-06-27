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
#include "Sort.h"

enum class StructType {
    Array,
    Stack,
    Queue
};
void CreateMenuAndConnect(MainWindow *window, Ui::MainWindow *ui){

    auto struct_menu = new QMenu("数据结构");
    auto array_action = new QAction("数组");
    auto stack_action = new QAction("栈");
    auto queue_action = new QAction("队列");
    struct_menu->addAction(array_action);
    struct_menu->addAction(stack_action);
    struct_menu->addAction(queue_action);
    ui->menu_bar->addMenu(struct_menu);

    QObject::connect(array_action,&QAction::triggered,[=]{
        GraphicsView *graphicsView = new GraphicsView(window);
        graphicsView->setAlignment(Qt::AlignCenter);
        window->setCentralWidget(graphicsView);
        auto scene = new GraphicsScene();
        graphicsView->setScene(scene);
        auto a = new Array(scene);
        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
            a->Insert(0);
        });
    });
    QObject::connect(stack_action,&QAction::triggered,[=]{
        GraphicsView *graphicsView = new GraphicsView(window);
        graphicsView->setAlignment(Qt::AlignCenter);
        window->setCentralWidget(graphicsView);
        auto scene = new GraphicsScene();
        graphicsView->setScene(scene);
        auto a = new Array(scene);
        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
            a->Insert(0);
        });
    });


    auto sort_action = new QAction("排序");
    ui->menu_bar->addAction(sort_action);
    auto s = new Sort();
    QObject::connect(sort_action,&QAction::triggered,[=]{
        std::thread run(&Sort::begin,s);
        run.detach();
    });
    QObject::connect(s, &Sort::UPUI, [=]() {
        static int i = 0;
        i ++;
        window->statusBar()->showMessage(std::to_string(i).c_str());
    });


    auto log_action = new QAction("日志");
    ui->menu_bar->addAction(log_action);
    QObject::connect(log_action,&QAction::triggered,[=]{
        LOG.Show();
    });
}
MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    CreateMenuAndConnect(this,ui);



    LOG.AddLog("MainWindow构造函数");





    LOG.AddLog("MainWindow构造完成");
    LOG.AddLog("启动完成");
    ui->status_bar->showMessage("启动完成...");
}



