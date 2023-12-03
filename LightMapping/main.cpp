
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    w.setStyleSheet("background-color: black;");

//    w.show();
    return a.exec();
}
