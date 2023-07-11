#include "MainWindow.h"
#include <QApplication>

#include "MSTL/Array.hpp"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.show();
    return a.exec();
//    MSTL::Arrary<int > arr;
//
//    for (int i = 0;i < 5; ++i) {
//        arr.PushBack(i);
//    }
//
//    for (auto num : arr) {
//        qDebug() << num ;
//    }
}
