#include "simulation.h"
#include "animal.h"
#include "shark.h"
#include "fish.h"
#include "statistic.h"
#include <QDebug>
#include <QList>

Simulation::Simulation(Sea * seaSimulation, int p_refreshTime)
{
    this->seaSimulation = seaSimulation ;
    m_stat = new statistic(seaSimulation->getSimulationTurns());
    m_simuIsRun = false;
    turnAtTheEnd = 0;
    m_refreshTime = p_refreshTime;
}

void Simulation::run()
{
    qDebug() << "Function run" ;
    runSimulation();

    // Sleep between turns
    //QThread::msleep(1000);

}

void Simulation::runSimulation()
{
    turnAtTheEnd = 0;
    bool stopSimulation = false ;

    unsigned int currentTurn=0 ;
    unsigned int x=0 ;
    unsigned int y=0 ;

    unsigned int currentSharksNumber = 0 ;
    unsigned int currentFishesNumber = 0 ;

    // Statistic's variables
    unsigned int turnStartingSharksNumber = 0 ;
    unsigned int turnStartingFishesNumber = 0 ;
    //statistic statisticFile = statistic(this->seaSimulation->getSimulationTurns()) ;

    Animal * currentAnimal ;

    this->seaSimulation->Init();
    this->seaSimulation->Populate();

    qDebug() << "Start Simulation" ;
    m_simuIsRun = true;
    // Loop for the turns
    for(currentTurn=0; currentTurn< this->seaSimulation->getSimulationTurns() ; currentTurn++)
    {
        turnAtTheEnd = currentTurn;
        turnStartingSharksNumber = 0;
        turnStartingFishesNumber = 0;
        // Recuperation of all the sharks and all the fishes
        QList<Shark *> sharksToMove = QList<Shark *>() ;
        for(x=0 ; x<this->seaSimulation->getWidth() ; x++)
        {
            for(y=0 ; y<this->seaSimulation->getHeight() ; y++)
            {
                currentAnimal = this->seaSimulation->Get(x, y) ;

                if(currentAnimal != NULL)
                {
                    if(currentAnimal->GetType() == SHARK) {
                        sharksToMove.append((Shark*)currentAnimal);
                        turnStartingSharksNumber++;
                    }
                    else if(currentAnimal->GetType() == FISH)
                        turnStartingFishesNumber++;
                }
            }
        }
        currentSharksNumber = sharksToMove.length() ;

        // Shark turns
        qDebug() << "Sharks turn to move : " << currentSharksNumber ;
        while(!sharksToMove.isEmpty())
        {
            currentAnimal = sharksToMove.takeFirst();
            currentAnimal->Move();
        }

        // Recuperation of all the fishes (some could have been eaten by the sharks)
        QList<Fish *> fishesToMove = QList<Fish *>() ;
        for(x=0 ; x<this->seaSimulation->getWidth() ; x++)
        {
            for(y=0 ; y<this->seaSimulation->getHeight() ; y++)
            {
                currentAnimal = this->seaSimulation->Get(x, y) ;

                if(currentAnimal != NULL && currentAnimal->GetType() == FISH)
                        fishesToMove.append((Fish*)currentAnimal);
            }
        }
        currentFishesNumber = fishesToMove.length() ;


        // Fishes turns
        qDebug() << "Fishes turn to move : " << currentFishesNumber ;
        while(!fishesToMove.isEmpty())
        {
            currentAnimal = fishesToMove.takeFirst();
            currentAnimal->Move();
        }
        this->seaSimulation->Clean();


        // Statistics we save the number of sharks and the number of fishes for each turn
        m_stat->addTurn(turnStartingSharksNumber, turnStartingFishesNumber);


        if(stopSimulation)
        {
            qDebug() << "No more animals, simulation stopped at turn "<<currentTurn ;
            break ;
        }

        // If there is no more animals we stop the simulation
        if(currentSharksNumber == 0 || currentFishesNumber == 0 )
        {
            stopSimulation = true ;
        }
        QThread::msleep(m_refreshTime);
    }
     m_simuIsRun = false;
    qDebug() << "End Simulation" ;
}
