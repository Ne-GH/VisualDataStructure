#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
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
class MainWindow : public QMainWindow {
    Q_OBJECT
private slots:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Log logs;
    StructureType cur_structure_type;
    AlgorithmType cur_algorithm_type;
    Ui::MainWindow *ui;
    QPixmap pixmap;
public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Log &GetLog();
    QPixmap &GetPixmap();

    StructureType GetCurStructureType();
    void SetCurStructureType(StructureType structure_type);
    AlgorithmType GetCurAlgorithmType();
    void SetCurAlgorithmType(AlgorithmType algorithm_type);


};
#endif // MAINWINDOW_H
