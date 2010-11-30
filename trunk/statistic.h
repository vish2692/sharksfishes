#ifndef STATISTIC_H
#define STATISTIC_H

#include <QFile>
#include <QTextStream>

class statistic
{
private :
        QFile * stats ;
        QTextStream * out ;
        unsigned int simulationTurns ;
public:
    statistic(unsigned int simulationTurns);
    ~statistic();
    void addTurn(unsigned int sharksNumber, unsigned int fishesNumber);
    double* getFishes();
    double* getSharks();
};

#endif // STATISTIC_H
