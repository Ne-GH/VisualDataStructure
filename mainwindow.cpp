#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
// #include <utility>
using std::cout,std::endl;


static void Init(MainWindow *window,Ui::MainWindow *ui) {
    Log &log = window->GetLog();

    log.AddLog("初始化MainWindow成员变量");
    window->SetCurStructureType(StructureType::None);
    window->SetCurAlgorithmType(AlgorithmType::None);
    log.AddLog("初始化MainWindow成员变量结束");

    log.AddLog("设置菜单可选信息");
    ui->arrary_action->setCheckable(true);

    log.AddLog("设置菜单可选信息结束");


}
static void Connect(MainWindow *window,Ui::MainWindow *ui) {
    Log &log = window->GetLog();
    log.AddLog("开始绑定信号和槽");

    QObject::connect(ui->show_log_action,&QAction::triggered,window,[=]{

        window->GetLog().AddWringLog("Test");
        window->GetLog().AddErrorLog("Test");
        window->GetLog().Show();
    });

    log.AddLog("绑定信号和槽结束");
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

Log &MainWindow::GetLog() {
    return logs;
}

