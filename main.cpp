#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("Spare Parts Management System");
    window.resize(1200, 800);
    window.show();
    window.raise();
    window.activateWindow();
    return app.exec();
}

