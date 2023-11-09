/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 15:11
*******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "GraphicsView.h"
#include <QGridLayout>

namespace Ui{
    class MainWindow;
}



class MainWindow : public QMainWindow {
Q_OBJECT

    Ui::MainWindow *ui = nullptr;

    QWidget *struct_window = nullptr;
    QWidget *sort_window = nullptr;

    QGridLayout *sort_layout = nullptr;
    GraphicsView *struct_view = nullptr;
public:
    MainWindow(QWidget *prent = nullptr);
    ~MainWindow() = default;
};


#endif // _MAINWINDOW_H_
