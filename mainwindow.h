#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Logs/log.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class StructureType{
    None = 0,Arrary,List,Stack,Queue,String,Tree,Picture
};
enum class AlgorithmType{
    None = 0
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Log logs;
    StructureType cur_structure_type ;
    AlgorithmType cur_algorithm_type ;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
