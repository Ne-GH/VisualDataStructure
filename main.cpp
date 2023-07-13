#include "MainWindow.h"
#include <QApplication>

#include "MSTL/Array.hpp"
#include "MSTL/List.hpp"

int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    MainWindow main_window;
//    main_window.show();
//    return a.exec();

    MSTL::List<int> arr;
    for (int i = 1;i < 10; ++i) {
        arr.Insert(i,i);
    }

    for (auto num : arr) {
        qDebug() << num ;
    }

    arr.Clear();
}
