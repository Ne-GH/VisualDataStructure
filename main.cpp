#include "MainWindow.h"
#include <QApplication>

#include "MSTL/BinaryTree.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.show();
    return a.exec();
}
#include <QApplication>
//#include <QColorDialog>
//
//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);
//
//    QColor color = QColorDialog::getColor(Qt::red, nullptr, "选择颜色");
//
//    if (color.isValid()) {
//        // 颜色有效，可以使用它进行绘制或其他操作
//        // ...
//    }
//
//    return app.exec();
//}