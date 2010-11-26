#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ui_options.h"
#include "simulation.h"
#include "fish.h"
#include "shark.h"
#include <QDebug>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    return a.exec();
    qDebug() << "Start prog" ;

    Fish::InitVars(100, 20, 5, 10);
    Shark::InitVars(100, 20, 5, 10, 50);

    Sea * s = new Sea(50, 50, 1000, 750, 750);

    s->Init();
    s->Populate();

    Simulation * sim = new Simulation(s);
    sim->runSimulation();
    qDebug() << "End prog" ;
    return 1;
}
