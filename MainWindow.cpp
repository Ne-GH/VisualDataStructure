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




template <typename T>
void ConnectStructAction(QMainWindow *window, StructWindow *struct_window,QMenu *struct_menu,std::string struct_name) {
    auto action = new QAction(struct_name.c_str());
    struct_menu->addAction(action);
    QObject::connect(action,&QAction::triggered,[=]{
        window->centralWidget()->setParent(nullptr);
        window->setCentralWidget(struct_window->window);
        auto scene = new GraphicsScene();
        struct_window->view->setScene(scene);
        auto visual_arr = new T(scene);
        QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
            visual_arr->Insert(0);
        });
        QObject::connect(scene,&GraphicsScene::MenuDel,[=](QGraphicsItem *item) {
            visual_arr->Remove(item);
        });
    });
}

void ConnectSortAction(MainWindow *window,SortWindow *sort_window,QMenu *menu,SortType sort_type,std::string sort_name) {
    auto action = new QAction(sort_name.c_str());
    menu->addAction(action);
    QObject::connect(action,&QAction::triggered,[=]{
        sort_window->Stop();
        sort_window->ReSetRandomNumbers();
        sort_window->SetSortType(sort_type);
        window->centralWidget()->setParent(nullptr);
        window->setCentralWidget(sort_window->window);
    });
}


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    // CreateMenuAndConnect(this,ui);
    setWindowTitle("VisualStructure");
    setWindowIcon(QPixmap(":/Resource/About.png"));



    auto struct_window = new StructWindow();
    auto struct_menu = new QMenu("数据结构");
    ui->menu_bar->addMenu(struct_menu);

    ConnectStructAction<VisualArray>(this,struct_window,struct_menu,"数组");
    ConnectStructAction<VisualStack>(this,struct_window,struct_menu,"栈");
    ConnectStructAction<VisualQueue>(this,struct_window,struct_menu,"队列");
    ConnectStructAction<VisualList>(this,struct_window,struct_menu,"链表");
    ConnectStructAction<VisualTree>(this,struct_window,struct_menu,"二叉树");



    auto sort_window = new SortWindow();
    auto sort_menu = new QMenu("排序");
    ui->menu_bar->addMenu(sort_menu);
    ConnectSortAction(this,sort_window,sort_menu,SortType::BUBBLE_SORT,"冒泡排序");
    ConnectSortAction(this,sort_window,sort_menu,SortType::SELECTION_SORT,"选择排序");
    ConnectSortAction(this,sort_window,sort_menu,SortType::INSERTION_SORT,"插入排序");
    ConnectSortAction(this,sort_window,sort_menu,SortType::QUICK_SORT,"快速排序");
    ConnectSortAction(this,sort_window,sort_menu,SortType::MERGE_SORT,"归并排序");
    ConnectSortAction(this,sort_window,sort_menu,SortType::STD_SORT,"std::sort");


//    auto std_sort_action = new QAction("std::sort");
//    sort_menu->addAction(std_sort_action);
//

//    QObject::connect(std_sort_action,&QAction::triggered,[=]{
//        centralWidget()->setParent(nullptr);
//        sort_window->SetSortType(SortType::STD_SORT);
//        setCentralWidget(sort_window->window);
//    });
    QObject::connect(sort_window,&SortWindow::PauseSig,[=]{
        BarMessage("暂停...");
    });
    QObject::connect(sort_window,&SortWindow::ContinueSig,[=]{
        BarMessage("继续...");
    });
    QObject::connect(sort_window,&SortWindow::FinishSig,[=]{
        BarMessage("完成...");
    });
    QObject::connect(sort_window,&SortWindow::StopSig,[=]{
        BarMessage("停止...");
    });

//    ConnectSortAction<&VisualSort::BubbleSort>(this,sort_window,sort_menu,"冒泡排序");

//    QObject::connect(sort_window,&SortWindow::Start,[=]{
//        BarMessage("排序中...");
//    });
//    QObject::connect(sort_window,&SortWindow::Pause,[=]{
//        BarMessage("排序暂停...");
//    });
//    QObject::connect(sort_window,&SortWindow::Stop,[=]{
//        BarMessage("排序停止...");
//    });

//    auto bubble_sort = new QAction("冒泡排序");
//    sort_menu->addAction(bubble_sort);
//    QObject::connect(bubble_sort,&QAction::triggered,[=]{
//        centralWidget()->setParent(nullptr);
//        setCentralWidget(sort_window->window);
//        auto visual_sort = new VisualSort(sort_window);
//////
//        visual_sort->moveToThread(sort_window->sort_thread);
//        QObject::connect(sort_window->sort_thread,&QThread::started,visual_sort,&VisualSort::BubbleSort);
//        sort_window->sort_thread->start();
//        QObject::connect(visual_sort,&VisualSort::UPUI,[=] mutable {
//            visual_sort->UpUI();
//        });
//    });




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


    BarMessage("启动完成...");

}

void MainWindow::BarMessage(std::string &&mes) {
    ui->status_bar->showMessage(mes.c_str());
}



