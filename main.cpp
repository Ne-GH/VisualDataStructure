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

    for (int i = 0;i < 5; ++i) {
        arr.Push_back(i);
    }

    for (auto num : arr) {
        qDebug() << num;
    }
}
