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



