#include "mainwindow.h"
#include "startwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartWindow w;
    w.show();

//    MainWindow w;
//    w.show();

    return a.exec();
}
