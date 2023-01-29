#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedLayout>

#include "Array/Array.hpp"

using std::cout,std::endl;

static void Init(MainWindow *window,Ui::MainWindow *ui) {

    Log &log = window->GetLog();

    log.AddLog("设置标题");
    window->setWindowTitle("DataStructureVisualization");

    log.AddLog("初始化MainWindow成员变量");
    window->SetCurStructureType(StructureType::None);
    window->SetCurAlgorithmType(AlgorithmType::None);
    log.AddLog("初始化MainWindow成员变量结束");




}

static void Connect(MainWindow *window,Ui::MainWindow *ui) {
    Log &log = window->GetLog();
    log.AddLog("开始绑定信号和槽");

    auto log_menu = new QAction("日志");
    auto setting_menu = new QAction("设置");
    ui->menu_bar->addAction(log_menu);
    ui->menu_bar->addAction(setting_menu);


    QObject::connect(log_menu,&QAction::triggered,window,[=](){
        window->GetLog().Show();
    });


    auto stacked_layout = new QStackedLayout();
    stacked_layout->addWidget(ui->array_widget);
    stacked_layout->addWidget(ui->list_widget);
    QObject::connect(ui->structure_list,&QListWidget::currentRowChanged,stacked_layout,&QStackedLayout::setCurrentIndex);;
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


    resize(600,600);
    pixmap = QPixmap(500,500);
    pixmap.fill(Qt::yellow);


    logs.AddLog("启动完成");
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


void MainWindow::resizeEvent(QResizeEvent *event) {

}

void MainWindow::paintEvent(QPaintEvent *event) {

//    Array arr;
//    arr.PushBack(10);
//    arr.PushBack(20);
//    arr.PushBack(30);
//    arr.PushBack(40);
//    arr.PushBack(50);
//    arr.PushBack(60);
//
//    arr.Draw(this);

}

QPixmap &MainWindow::GetPixmap() {
    return pixmap;
}
