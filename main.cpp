#include "MainWindow.h"
#include <QApplication>

#include "MSTL/Array.hpp"
#include "MSTL/List.hpp"
#include "MSTL/Queue.hpp"

int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    MainWindow main_window;
//    main_window.show();
//    return a.exec();

    MSTL::Queue<int> arr;
    for (int i = 0;i < 10; ++i) {
        arr.PushBack(i);
    }

    auto tmp = arr.PopFront();
    qDebug() << tmp;
    auto &t = arr.Front();
    t = 20;
    qDebug() << arr.PopFront();



}
