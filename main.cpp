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
    Fish::InitVars(100, 20, 5, 10);
    Shark::InitVars(100, 20, 5, 10, 50);

    Sea * s = new Sea(10, 10, 1000, 50, 20);
    //s->Init();
    //s->Populate();

    Simulation * sim = new Simulation(s);
    sim->runSimulation();
    return 1;
}
