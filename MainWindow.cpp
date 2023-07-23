/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 15:11
*******************************************************************************/

#include <random>
#include <QThread>
#include <QPushButton>
#include <QSlider>
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
#include <memory>
enum class StructType {
    Array,
    Stack,
    Queue
};
void CreateSortLayout(QWidget *window,Ui::MainWindow *ui) {
    QBarSet *set0 = new QBarSet("");
    QBarSeries *series = new QBarSeries();
    QChart *chart = new QChart();
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();
    QChartView *chartView = new QChartView(chart);
    QStringList categories;
    series->append(set0);
    chart->addSeries(series);
    chart->setTitle("");
    // chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationOptions(QChart::NoAnimation);
//    for (int i = 0;i < visual_sort->GetRandomVector().size(); ++i) {
//        categories << std::to_string(i).c_str();
//    }
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
//    window->setCentralWidget(chartView);


    ui->layout->addWidget(chartView,0,0,10,10);




    QSlider *lider = new QSlider(Qt::Horizontal);

    auto start_but = new QPushButton("开始");
    auto pause_but = new QPushButton("暂停");
    auto stop_but = new QPushButton("停止");

    ui->layout->addWidget(start_but, 10, 1, 1, 1);
    ui->layout->addWidget(pause_but, 10, 3, 1, 1);
    ui->layout->addWidget(stop_but, 10, 5, 1, 1);
    ui->layout->addWidget(lider, 10, 7, 1, 2);

}

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
        auto list = std::make_shared<VisualList>(scene);
        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
            list->Insert(10);
        });
        QObject::connect(scene,&GraphicsScene::MenuDel,[=](QGraphicsItem *item) {
            list->Remove(item);
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
        QObject::connect(scene,&GraphicsScene::MenuDel,[=](QGraphicsItem *item){
            arr->Remove(item);
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
    auto sort_menu = new QMenu("排序");
    auto std_sort_action = new QAction("std::sort");
    sort_menu->addAction(std_sort_action);
    ui->menu_bar->addMenu(sort_menu);
    QObject::connect(std_sort_action,&QAction::triggered,[=]{
        SetChart();
        visual_sort->moveToThread(run);
        QObject::connect(run,&QThread::started,visual_sort,&VisualSort::StdSort);
        run->start();
    });
    auto bubble_sort = new QAction("冒泡排序");
    sort_menu->addAction(bubble_sort);
    QObject::connect(bubble_sort,&QAction::triggered,[=]{
        SetChart();
        visual_sort->moveToThread(run);
        QObject::connect(run,&QThread::started,visual_sort,&VisualSort::BubbleSort);
        run->start();
    });
    auto selection_sort = new QAction("选择排序");
    sort_menu->addAction(selection_sort);
    QObject::connect(selection_sort,&QAction::triggered,[=]{
        SetChart();
        visual_sort->moveToThread(run);
        QObject::connect(run,&QThread::started,visual_sort,&VisualSort::SelectionSort);
        run->start();
    });
    auto insertion_sort = new QAction("插入排序");
    sort_menu->addAction(insertion_sort);
    QObject::connect(insertion_sort,&QAction::triggered,[=]{
        SetChart();
        visual_sort->moveToThread(run);
        QObject::connect(run,&QThread::started,visual_sort,&VisualSort::InsertionSort);
        run->start();
    });
    auto quick_sort = new QAction("快排");
    sort_menu->addAction(quick_sort);
    QObject::connect(quick_sort,&QAction::triggered,[=]{
        SetChart();
        visual_sort->moveToThread(run);
        QObject::connect(run,&QThread::started,visual_sort,&VisualSort::QuickSort);
        run->start();
    });

    auto merge_sort = new QAction("归并");
    sort_menu->addAction(merge_sort);
    QObject::connect(merge_sort,&QAction::triggered,[=]{
        SetChart();
        visual_sort->moveToThread(run);
        QObject::connect(run,&QThread::started,visual_sort,&VisualSort::MergeSort);
        run->start();
    });

    QObject::connect(visual_sort,&VisualSort::UPUI,[=]mutable  {
        auto vec = visual_sort->GetRandomVector();
        set0->remove(0,vec.size());
        for (auto num : vec) {
            *set0 << num;
        }
    });


    auto setting_action = new QAction("设置");
    ui->menu_bar->addAction(setting_action);
    QObject::connect(setting_action,&QAction::triggered,[=]{
        Setting setting_dialog;
        setting_dialog.setWindowTitle("设置");
        setting_dialog.LoadSettingFile();
        setting_dialog.exec();
    });

}
MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    CreateMenuAndConnect(this,ui);

    CreateSortLayout(this,ui);






    ui->status_bar->showMessage("启动完成...");
}



