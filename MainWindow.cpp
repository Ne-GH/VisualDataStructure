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
        std::this_thread::sleep_for(std::chrono::milliseconds{10});
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


    QObject::connect(sort_window,&SortWindow::StartSig,[=]{
        BarMessage("开始...");
    });
    QObject::connect(sort_window,&SortWindow::PauseSig,[=]{
        BarMessage("暂停...");
    });
    QObject::connect(sort_window,&SortWindow::ContinueSig,[=]{
        BarMessage("继续...");
    });
    QObject::connect(sort_window,&SortWindow::FinishSig,[=]{
        BarMessage("完成...");
    });




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



