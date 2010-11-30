#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ui_options.h"
#include "simulation.h"
#include "fish.h"
#include "shark.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    return a.exec();

//    //int maxLife, int reproductionCycle, int decayTime, int matureTime, int starvationTime
//    Fish::InitVars(100, 30, 5, 10);
//    Shark::InitVars(100, 30, 5, 10, 30);
//
//    // int width, int height, int simulation_turns, int starting_fishes, int starting_sharks
//    Sea * s = new Sea(10, 10, 1000, 50, 20);
//
//    Simulation * sim = new Simulation(s);
//    sim->runSimulation();
//    return 1;
}
