#include "MainWindow.h"
#include <QApplication>

#include "MSTL/BinaryTree.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.show();
    return a.exec();
}
