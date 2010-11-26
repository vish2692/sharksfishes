#ifndef SIMULATION_H
#define SIMULATION_H
#include <QThread>
#include "sea.h"

class Simulation : public QThread
{
private :
    Sea * seaSimulation ;
public:
    Simulation(Sea * seaSimulation);
    virtual void run();
    void runSimulation();
};

#endif // SIMULATION_H
