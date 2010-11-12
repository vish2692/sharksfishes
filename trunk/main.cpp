#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ui_options.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    return a.exec();
}
