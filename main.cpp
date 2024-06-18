
#include "MainWindow.h"
#include <QApplication>

import Config;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.show();
    return a.exec();
}