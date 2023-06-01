/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/06/01 15:11
*******************************************************************************/

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QWidget>
#include <QMainWindow>

namespace Ui{
    class MainWindow;
}
class MainWindow : public QMainWindow {
    Q_OBJECT

    Ui::MainWindow *ui = nullptr;
public:
    MainWindow(QWidget *prent = nullptr);
    ~MainWindow() = default;


};


#endif // _MAINWINDOW_H_
