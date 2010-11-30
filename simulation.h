#ifndef SIMULATION_H
#define SIMULATION_H
#include <QThread>
#include "sea.h"
#include "statistic.h"


class Simulation : public QThread
{
private :
    Sea * seaSimulation ;
public:
    Simulation(Sea * seaSimulation, int p_refreshTime);
    virtual void run();
    void runSimulation();
    inline statistic * GetStat(){return m_stat;}
    inline void SetStat(statistic * p_stat){m_stat = p_stat;}
    inline bool GetSimuState(){return m_simuIsRun;}
    inline unsigned int GetTurnAtTheEnd(){return turnAtTheEnd;}

private:
    statistic *m_stat;
    bool m_simuIsRun;
    unsigned int turnAtTheEnd ;
    int m_refreshTime;
};

#endif // SIMULATION_H
