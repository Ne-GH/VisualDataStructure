/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 15:11
*******************************************************************************/

#include <iostream>
#include <random>
#include <QTimer>
#include <thread>
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
#include "Logs/Log.h"

#include "Graphics/GraphicsScene.h"
#include "Graphics/GraphicsItem.h"
#include "Graphics/GraphicsView.h"
#include "Structure/Array.hpp"

class CustomBarSet : public QObject, public QGraphicsRectItem
{
public:
    CustomBarSet(const QString& label, qreal value, QGraphicsItem* parent = nullptr)
            : QObject(nullptr), QGraphicsRectItem(parent)
    {
        setLabel(label);
        setValue(value);
        setBrush(Qt::NoBrush); // 设置颜色方块为空画刷，即不绘制颜色方块
    }

    void setLabel(const QString& label)
    {
        m_label = label;
    }

    void setValue(qreal value)
    {
        m_value = value;
        setRect(QRectF(0, 0, m_value, 10)); // 设置柱状图项的大小
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override
    {
        // 绘制柱状图项的标签
        painter->drawText(boundingRect().adjusted(5, 0, -5, 0), Qt::AlignCenter, m_label);
    }

private:
    QString m_label;
    qreal m_value;
};
MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent),
                        ui(new Ui::MainWindow){
    ui->setupUi(this);
    resize(850,650);
    LOG.AddLog("MainWindow构造函数");
    auto log_action = new QAction("日志");
    ui->menu_bar->addAction(log_action);
    connect(log_action,&QAction::triggered,[=]{
        LOG.Show();
    });

    // 创建 QGraphicsView 和 QGraphicsScene 对象
//    GraphicsView *graphicsView = new GraphicsView(this);
//    graphicsView->setAlignment(Qt::AlignCenter);
//    setCentralWidget(graphicsView);
//    auto scene = new GraphicsScene();
//    graphicsView->setScene(scene);
////    graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatioByExpanding);
////    view->scale(scaleFactor, scaleFactor);
//
//    auto a = new Array(scene);
//
//    QObject::connect(scene,&GraphicsScene::MenuAdd,[=]{
//        a->Insert(0);
//    });

    auto view = new QChartView();
    auto series = new QBarSeries();
    auto chart = new QChart();
    setCentralWidget(view);

    view->setChart(chart);
    chart->addSeries(series);
    view->show();

    auto timer = new QTimer(this);
    auto vec = new std::vector<unsigned>(100);
    std::default_random_engine rand_engine;
    for (auto& p : *vec) {
        p = rand() % 100;
    }

    auto pi = new int;
    *pi = 0;

    QObject::connect(timer,&QTimer::timeout,[=]{

        std::partial_sort(vec->begin(),vec->begin()+*pi,vec->end());
        *pi > 100 ? 100 : ++*pi;

        chart->removeAllSeries();
        auto series = new QBarSeries();
        for (auto p : *vec) {
            auto barSet = new QBarSet("");
            *barSet << p;
            series->append(barSet);
        }
//        series->setLabelsVisible(true);  //设置数据标签可见
        chart->addSeries(series);
        view->chart()->update();

    });
    timer->start(100);



    LOG.AddLog("MainWindow构造完成");
    LOG.AddLog("启动完成");
    ui->status_bar->showMessage("启动完成...");
}

