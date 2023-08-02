/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 15:11
*******************************************************************************/

#include <random>
#include <QThread>
#include <QPushButton>
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

#include <memory>

void CreateMenuAndConnect(MainWindow *window, Ui::MainWindow *ui){

    auto struct_menu = new QMenu("数据结构");

#define CONNECT_STRUCT(action_string,visual_type) \
{                                              \
    auto action = new QAction(action_string);     \
    struct_menu->addAction(action);               \
    QObject::connect(action,&QAction::triggered,[=]{\
    auto graphicsView = new GraphicsView(window);\
    graphicsView->setAlignment(Qt::AlignCenter);\
    window->setCentralWidget(graphicsView);\
    auto scene = new GraphicsScene();\
    graphicsView->setScene(scene);\
    auto visual = std::make_shared<visual_type>(scene);\
    QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{\
        visual->Insert(0);\
    });\
    QObject::connect(scene,&GraphicsScene::MenuDel,[=](QGraphicsItem *item) {\
        visual->Remove(item);\
    });\
}); \
}

    CONNECT_STRUCT("数组",VisualArray);
    CONNECT_STRUCT("链表",VisualList);


    ui->menu_bar->addMenu(struct_menu);


#undef CONNECT_STRUCT

#define CAT(a,b) a: ## :b
#define GETSORTNAME(sort_name) CAT(&VisualSort,sort_name)
#define CONNECT_SORT(action_name,sort_name) \
    auto sort_name = new QAction(action_name);\
    sort_menu->addAction(sort_name);\
    QObject::connect(sort_name,&QAction::triggered,[=]{ \
        auto visual_sort = new VisualSort();\
        auto sort_thread = new QThread();\
        visual_sort->GetRandomVector(100);\
        visual_sort->CreateSortLayout(ui->layout);\
        visual_sort->moveToThread(sort_thread);\
        QObject::connect(sort_thread,&QThread::started,visual_sort,GETSORTNAME(sort_name));\
        sort_thread->start();\
        QObject::connect(visual_sort,&VisualSort::UPUI,[=] mutable {\
            visual_sort->UpUI();\
        });\
    });\

    auto sort_menu = new QMenu("排序");
    ui->menu_bar->addMenu(sort_menu);
    CONNECT_SORT("std::sort",StdSort);
    CONNECT_SORT("冒泡排序",BubbleSort);
    CONNECT_SORT("选择排序",SelectionSort);
    CONNECT_SORT("插入排序",InsertionSort);
    CONNECT_SORT("快速排序",QuickSort);
    CONNECT_SORT("归并排序",MergeSort);

#undef CAT
#undef GETSORTNAME
#undef CONNECT_SORT


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







    ui->status_bar->showMessage("启动完成...");
}



