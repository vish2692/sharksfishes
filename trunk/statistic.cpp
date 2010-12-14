#include "statistic.h"
#include <QDebug>
#include <string.h>

statistic::statistic(unsigned int simulationTurns)
{
    this->simulationTurns = simulationTurns ;
    this->stats = new QFile("statistiques");
    if (!this->stats->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "The statistic file could not be open.";
        return;
    }
    this->out = new QTextStream(this->stats);
}

statistic::~statistic()
{
    this->stats->close();
}

void statistic::addTurn(unsigned int sharksNumber, unsigned int fishesNumber)
{
    *this->out << fishesNumber << " " << sharksNumber << " " << endl;
}

double* statistic::getFishes()
{
    double fishesCount[this->simulationTurns];
    memset(fishesCount, 0, this->simulationTurns);
    this->stats->close();
    if (!this->stats->open(QIODevice::ReadOnly)) {
        qDebug() << "The statistic file could not be open.";
        return fishesCount ;
    }

    int currentTurn = 0 ;
    char * p ;
    char buf[1024];
    char charTurnNumber[1024];
    unsigned int intTurnNumber = 0 ;
    qint64 lineLength = this->stats->readLine(buf, sizeof(buf));

    while(lineLength != -1)
    {
        lineLength = this->stats->readLine(buf, sizeof(buf));

        p = strchr(buf, ' ');
        if(p != NULL)
        {
            strncpy(charTurnNumber, buf, p - buf + 1);
            intTurnNumber = atoi(charTurnNumber);
            fishesCount[currentTurn] = (double)intTurnNumber ;
            currentTurn++ ;
            //qDebug() << intTurnNumber ;
        }
    }

    this->stats->close();

    return fishesCount ;
}

double* statistic::getSharks()
{
    double sharksCount[this->simulationTurns];
    memset(sharksCount, 0, this->simulationTurns);
    
    this->stats->close();
    if (!this->stats->open(QIODevice::ReadOnly)) {
        qDebug() << "The statistic file could not be open.";
        return sharksCount ;
    }

    int currentTurn = 0 ;
    char * p ;
    char * p2 ;
    char buf[1024];
    char charTurnNumber[1024];
    unsigned int intTurnNumber = 0 ;
    qint64 lineLength = this->stats->readLine(buf, sizeof(buf));

    while(lineLength != -1)
    {
        lineLength = this->stats->readLine(buf, sizeof(buf));

        p = strchr(buf, ' ');
        if(p != NULL)
        {
            // We search the second space
            p2 = strchr(p+1, ' ');
            {
                if(p2 != NULL)
                strncpy(charTurnNumber, p, p2 - buf + 1);
                intTurnNumber = atoi(charTurnNumber);
                sharksCount[currentTurn] = (double)intTurnNumber ;
                currentTurn++ ;
                //qDebug() << intTurnNumber ;
            }
        }
    }

    this->stats->close();

    return sharksCount ;
}
