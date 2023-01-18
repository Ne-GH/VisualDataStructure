#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
using std::cout,std::endl;


static void Init(MainWindow *window,Ui::MainWindow *ui) {
    window->logs.AddLog("初始化MainWindow成员变量");
    window->cur_structure_type = StructureType::None;
    window->cur_algorithm_type = AlgorithmType::None;
    window->logs.AddLog("初始化MainWindow成员变量结束");

    window->logs.AddLog("设置菜单可选信息");
    ui->arrary_action->setCheckable(true);
//    ui->list_action->setCheckable(true);
//    ui->stack_action->setCheckable(true);
//    ui->queue_action->setCheckable(true);
//    ui->string_action->setCheckable(true);
//    ui->tree_action->setCheckable(true);
//    ui->picture_action->setCheckable(true);
//
//    ui->install_action->setCheckable(true);
//    ui->delete_action->setCheckable(true);
//    ui->sort_action->setCheckable(true);
    window->logs.AddLog("设置菜单可选信息结束");


}
static void Connect(MainWindow *window,Ui::MainWindow *ui) {
    window->logs.AddLog("开始绑定信号和槽");

    QObject::connect(ui->show_log_action,&QAction::triggered,window,[=]{
        window->logs.Show();
        window->logs.AddErrorLog("Test Error");
        window->logs.AddWringLog("Test Wring");
    });

    window->logs.AddLog("绑定信号和槽结束");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    /* 初始化成员变量 */
    logs.AddLog("启动...");
    Init(this,ui);

    Connect(this,ui);



}

MainWindow::~MainWindow() {
    delete ui;
}
