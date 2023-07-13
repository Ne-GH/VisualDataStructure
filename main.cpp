#include "MainWindow.h"
#include <QApplication>

#include "MSTL/Array.hpp"
#include "MSTL/List.hpp"
#include "MSTL/Stack.hpp"

int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    MainWindow main_window;
//    main_window.show();
//    return a.exec();


    MSTL::Stack<int> arr;
    for (int i = 0;i < 20; ++i) {
        arr.Push(i);
    }

    int tmp = arr.Pop();
    std::cout << tmp << std::endl;



}
