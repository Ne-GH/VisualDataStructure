#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QPainterPath>
using std::cout,std::endl;

static void Init(MainWindow *window,Ui::MainWindow *ui) {

    Log &log = window->GetLog();

    log.AddLog("设置标题");
    window->setWindowTitle("DataStructureVisualization");

    log.AddLog("初始化MainWindow成员变量");
    window->SetCurStructureType(StructureType::None);
    window->SetCurAlgorithmType(AlgorithmType::None);
    log.AddLog("初始化MainWindow成员变量结束");

    log.AddLog("设置菜单可选信息");
    ui->arrary_action->setCheckable(true);

    log.AddLog("设置菜单可选信息结束");

    log.AddLog("初始化Pixmap");
    auto &pixmap = window->GetPixmap();
    pixmap = *new QPixmap(1920,1080);
    pixmap.fill(Qt::white);

    log.AddLog("初始化Pixmap结束");

}

static void Connect(MainWindow *window,Ui::MainWindow *ui) {
    Log &log = window->GetLog();
    log.AddLog("开始绑定信号和槽");

    QObject::connect(ui->show_log_action,&QAction::triggered,window,[=]{
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
/*    QPainter painter(this);
    QPixmap pix(QWidget::width(),QWidget::height());
    pix.fill(Qt::yellow);
    QPainter pp(&pix);
    QPainterPath path;
    pp.setRenderHint(QPainter::Antialiasing);
    pp.setRenderHint(QPainter::SmoothPixmapTransform);
    path.lineTo(390,390);
    path.moveTo(0,ui->menu_bar->height());
    path.addEllipse(100,200,50,50);
    path.lineTo(390,390);

    pp.drawPath(path);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(0,0,pix);*/

}

QPixmap &MainWindow::GetPixmap() {
    return pixmap;
}
