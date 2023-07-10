#include "MainWindow.h"
#include <QApplication>


#include "MSTL/Array.hpp"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.show();
    return a.exec();
//    MSTL::Arrary<int> arr;
//    arr.PushBack(10);
//    arr.PushBack(20);
//    arr.PushBack(30);
//
//
//    for (auto it = arr.begin();it != arr.end();) {
//        if (*it == 30) {
//            it = arr.Delete(it);
//        }
//        else {
//            ++it;
//        }
//    }
//
//    for (auto num : arr) {
//        qDebug() << num;
//    }

    return 0;
}
