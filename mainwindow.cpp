#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include <utility>
using std::cout,std::endl;


static void Init(MainWindow *window,Ui::MainWindow *ui) {
    window->AddLog("初始化MainWindow成员变量");
    window->SetCurStructureType(StructureType::None);
    window->SetCurAlgorithmType(AlgorithmType::None);
    window->AddLog("初始化MainWindow成员变量结束");

    window->AddLog("设置菜单可选信息");
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
    window->AddLog("设置菜单可选信息结束");


}
static void Connect(MainWindow *window,Ui::MainWindow *ui) {
    window->AddLog("开始绑定信号和槽");

    QObject::connect(ui->show_log_action,&QAction::triggered,window,[=]{
        window->ShowLog();
        window->AddErrorLog("Test Error");
        window->AddWringLog("Test Wring");
    });

    window->AddLog("绑定信号和槽结束");
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

void MainWindow::AddLog(std::string message) {
    logs.AddLog(std::move(message));
}

void MainWindow::AddWringLog(std::string message) {
    logs.AddWringLog(std::move(message));
}

void MainWindow::AddErrorLog(std::string message) {
    logs.AddErrorLog(std::move(message));
}

StructureType MainWindow::GetCurStructureType() {
    return cur_structure_type;
}

void MainWindow::SetCurStructureType(StructureType structure_type) {
    cur_structure_type = structure_type;
}

AlgorithmType MainWindow::GetCurAlgorithmType() {
    return cur_algorithm_type;
}

void MainWindow::SetCurAlgorithmType(AlgorithmType algorithm_type) {
    cur_algorithm_type = algorithm_type;
}

void MainWindow::ShowLog() {
    logs.Show();
}

