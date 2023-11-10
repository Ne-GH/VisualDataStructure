/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 15:11
*******************************************************************************/

#include <QThread>
#include <QPushButton>
#include <algorithm>
#include <QLabel>
#include <QtCharts/QChart>
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "GraphicsScene.h"
#include "GraphicsItem.h"
#include "GraphicsView.h"

#include "VisualArray.hpp"
#include "VisualStack.hpp"
#include "VisualQueue.hpp"
#include "VisualList.hpp"
#include "VisualTree.hpp"
#include "VisualSort.h"

#include "AboutDialog.h"

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
    CONNECT_STRUCT("栈",VisualStack);
    CONNECT_STRUCT("队列",VisualQueue);
    CONNECT_STRUCT("链表",VisualList);
    CONNECT_STRUCT("二叉树",VisualTree);


    ui->menu_bar->addMenu(struct_menu);


#undef CONNECT_STRUCT

#define CAT(a,b) a: ## :b
#define GETSORTNAME(sort_name) CAT(&VisualSort,sort_name)
#define CONNECT_SORT(action_name,sort_name) \
    auto sort_name = new QAction(action_name);\
    sort_menu->addAction(sort_name);\
    QObject::connect(sort_name,&QAction::triggered,[=]{ \
        auto visual_sort = new VisuaSort();\
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
//    CONNECT_SORT("std::sort",StdSort);
//    CONNECT_SORT("冒泡排序",BubbleSort);
//    CONNECT_SORT("选择排序",SelectionSort);
//    CONNECT_SORT("插入排序",InsertionSort);
//    CONNECT_SORT("快速排序",QuickSort);
//    CONNECT_SORT("归并排序",MergeSort);

#undef CAT
#undef GETSORTNAME
#undef CONNECT_SORT

}




struct StructWindow {
    QWidget *window = nullptr;
    GraphicsView *view;
    QGridLayout *layout;

    StructWindow() {
        window = new QWidget(nullptr);
        view = new GraphicsView(nullptr);
        layout = new QGridLayout(nullptr);
        window->setLayout(layout);
        layout->addWidget(view);

        view->setAlignment(Qt::AlignCenter);
//        window->show();
//        auto but = new QPushButton(window);
    }
};





MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    // CreateMenuAndConnect(this,ui);
    setWindowTitle("VisualStructure");
    setWindowIcon(QPixmap(":/Resource/About.png"));



    StructWindow *struct_window = new StructWindow();

    auto struct_menu = new QMenu("数据结构");
    ui->menu_bar->addMenu(struct_menu);

    auto arr_action = new QAction("数组");
    struct_menu->addAction(arr_action);
    QObject::connect(arr_action,&QAction::triggered,[=] {
        centralWidget()->setParent(nullptr);
        setCentralWidget(struct_window->window);
        auto scene = new GraphicsScene();
        struct_window->view->setScene(scene);
        auto visual_arr = new VisualArray(scene);
        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
            visual_arr->Insert(0);
        });
        QObject::connect(scene,&GraphicsScene::MenuDel,[=](QGraphicsItem *item) {
            visual_arr->Remove(item);

        });
    });

    auto list_action = new QAction("链表");
    struct_menu->addAction(list_action);
    QObject::connect(list_action,&QAction::triggered,[=] {
        setCentralWidget(struct_window->window);
        auto scene = new GraphicsScene();
        struct_window->view->setScene(scene);
        auto visual_list = new VisualList(scene);
        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
            visual_list->Insert(0);
        });
        QObject::connect(scene,&GraphicsScene::MenuDel,[=](QGraphicsItem *item) {
            visual_list->Remove(item);
        });
    });
//
//    auto binary_tree_action = new QAction("二叉树");
//
//
//    struct_menu->addAction(binary_tree_action);
//    QObject::connect(binary_tree_action,&QAction::triggered,[=] {
//        ui->layout->addWidget(struct_view);
//        auto scene = new GraphicsScene();
//        struct_view->setScene(scene);
//        auto visual_tree = new VisualTree(scene);
//        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
//            visual_tree->Insert(0);
//        });
//        QObject::connect(scene,&GraphicsScene::MenuDel,[=](QGraphicsItem *item) {
//            visual_tree->Remove(item);
//        });
//    });
//
    //    CONNECT_STRUCT("数组",VisualArray);
    //    CONNECT_STRUCT("栈",VisualStack);
    //    CONNECT_STRUCT("队列",VisualQueue);
    //    CONNECT_STRUCT("链表",VisualList);
    //    CONNECT_STRUCT("二叉树",VisualTree);


    SortWindow *sort_window = new SortWindow();
    auto sort_menu = new QMenu("排序");
    ui->menu_bar->addMenu(sort_menu);

    auto bubble_sort = new QAction("冒泡排序");
    sort_menu->addAction(bubble_sort);
    QObject::connect(bubble_sort,&QAction::triggered,[=]{
        centralWidget()->setParent(nullptr);
        setCentralWidget(sort_window->window);
        auto visual_sort = new VisualSort(sort_window);
////
        visual_sort->moveToThread(sort_window->sort_thread);
        QObject::connect(sort_window->sort_thread,&QThread::started,visual_sort,&VisualSort::BubbleSort);
        sort_window->sort_thread->start();
        QObject::connect(visual_sort,&VisualSort::UPUI,[=] mutable {
            visual_sort->UpUI();
        });
    });




//    CONNECT_SORT("std::sort",StdSort);
//    CONNECT_SORT("冒泡排序",BubbleSort);
//    CONNECT_SORT("选择排序",SelectionSort);
//    CONNECT_SORT("插入排序",InsertionSort);
//    CONNECT_SORT("快速排序",QuickSort);
//    CONNECT_SORT("归并排序",MergeSort);



    auto setting_action = new QAction("设置");
    ui->menu_bar->addAction(setting_action);
    QObject::connect(setting_action,&QAction::triggered,[=]{
        Setting setting_dialog;
        setting_dialog.setWindowTitle("设置");
        setting_dialog.LoadSettingFile();
        setting_dialog.exec();
    });


    auto about_action = new QAction("关于");
    ui->menu_bar->addAction(about_action);
    QObject::connect(about_action,&QAction::triggered,[=]{
        AboutDialog about_dialog = AboutDialog();
        about_dialog.exec();
    });



    ui->status_bar->showMessage("启动完成...");

}



