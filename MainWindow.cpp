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
#include "VisualArray.hpp"
#include "VisualList.hpp"
#include "VisualSort.h"
#include "Array.hpp"
#include <QThread>
#include <QSplineSeries>
#include <QValueAxis>

enum class StructType {
    Array,
    Stack,
    Queue
};

void CreateMenuAndConnect(MainWindow *window, Ui::MainWindow *ui){

    auto struct_menu = new QMenu("数据结构");
    auto array_action = new QAction("数组");
    auto list_action = new QAction("链表");
    auto stack_action = new QAction("栈");
    auto queue_action = new QAction("队列");
    struct_menu->addAction(array_action);
    struct_menu->addAction(list_action);
    struct_menu->addAction(stack_action);
    struct_menu->addAction(queue_action);
    ui->menu_bar->addMenu(struct_menu);


    QObject::connect(list_action,&QAction::triggered,[=]{
        auto graphicsView = new GraphicsView(window);
        graphicsView->setAlignment(Qt::AlignCenter);
        window->setCentralWidget(graphicsView);
        auto scene = new GraphicsScene();
        graphicsView->setScene(scene);
        auto list = new VisualList(scene);
        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
            list->Insert(10);
        });

    });

    QObject::connect(array_action,&QAction::triggered,[=]{
        auto graphicsView = new GraphicsView(window);
        graphicsView->setAlignment(Qt::AlignCenter);
        window->setCentralWidget(graphicsView);
        auto scene = new GraphicsScene();
        graphicsView->setScene(scene);
        auto arr = new VisualArray(scene);
        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
            arr->Insert(0);
        });
    });
    QObject::connect(stack_action,&QAction::triggered,[=]{
        GraphicsView *graphicsView = new GraphicsView(window);
        graphicsView->setAlignment(Qt::AlignCenter);
        window->setCentralWidget(graphicsView);
        auto scene = new GraphicsScene();
        graphicsView->setScene(scene);
        auto a = new VisualArray(scene);
        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
            a->Insert(0);
        });
    });

    auto sort_menu = new QMenu("排序");
    auto std_sort_action = new QAction("std::sort");
    auto bubble_sort = new QAction("冒泡排序");
    sort_menu->addAction(std_sort_action);
    sort_menu->addAction(bubble_sort);
    ui->menu_bar->addMenu(sort_menu);
    auto visual_sort = new VisualSort();
    visual_sort->GetRandomVector(100);
    auto run = new QThread();

    QBarSet *set0 = new QBarSet("");
    QBarSeries *series = new QBarSeries();
    QChart *chart = new QChart();
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();
    QChartView *chartView = new QChartView(chart);
    auto SetChart = [=]{
        QStringList categories;
        series->append(set0);
        chart->addSeries(series);
        chart->setTitle("");
        // chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setAnimationOptions(QChart::NoAnimation);
        for (int i = 0;i < visual_sort->GetRandomVector().size(); ++i) {
            categories << std::to_string(i).c_str();
        }
        axisX->append(categories);
        axisX->setVisible(false);
        axisY->setVisible(false);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        axisY->setRange(0,100);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);
        chart->legend()->setVisible(false);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chartView->setRenderHint(QPainter::Antialiasing);
        window->setCentralWidget(chartView);
    };

    QObject::connect(std_sort_action,&QAction::triggered,[=]{
        SetChart();
        visual_sort->moveToThread(run);
        QObject::connect(run,&QThread::started,visual_sort,&VisualSort::StdSort);
        run->start();
    });
    QObject::connect(bubble_sort,&QAction::triggered,[=]{
        SetChart();
        visual_sort->moveToThread(run);
        QObject::connect(run,&QThread::started,visual_sort,&VisualSort::BubbleSort);
        run->start();
    });


    QObject::connect(visual_sort,&VisualSort::UPUI,[=]mutable  {
        auto vec = visual_sort->GetRandomVector();
        set0->remove(0,vec.size());
        for (auto num : vec) {
            *set0 << num;
        }
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



