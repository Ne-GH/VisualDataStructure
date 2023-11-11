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


public:
    MainWindow(QWidget *prent = nullptr);
    ~MainWindow() = default;
    void BarMessage(std::string &&);
};


#endif // _MAINWINDOW_H_
