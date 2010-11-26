#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ui_options.h"
#include "simulation.h"
#include <QDebug>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    return a.exec();
    qDebug() << "Start prog" ;
    Sea * s = new Sea(10, 10, 10, 5, 5);

    s->Init();
    s->Populate();

    Simulation * sim = new Simulation(s);
    sim->runSimulation();
    qDebug() << "End prog" ;
    return 1;
}
