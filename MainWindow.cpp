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


    auto sort_menu = new QMenu("排序");
    ui->menu_bar->addMenu(sort_menu);
    auto std_sort_action = new QAction("std::sort");
    sort_menu->addAction(std_sort_action);
    QObject::connect(std_sort_action,&QAction::triggered,[=]{
        auto visual_sort = new VisualSort();
        auto sort_thread = new QThread();
        visual_sort->GetRandomVector(100);
        visual_sort->CreateSortLayout(ui->layout);
        visual_sort->moveToThread(sort_thread);
        QObject::connect(sort_thread,&QThread::started,visual_sort,&VisualSort::StdSort);
        sort_thread->start();

        QObject::connect(visual_sort,&VisualSort::UPUI,[=]mutable  {
            auto vec = visual_sort->GetRandomVector();
            auto set = visual_sort->GetBarSet();
            set->remove(0,vec.size());
            for (auto num : vec) {
                *set << num;
            }
        });
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







    ui->status_bar->showMessage("启动完成...");
}



