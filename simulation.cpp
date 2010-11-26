#include "simulation.h"
#include "animal.h"
#include <QDebug>

Simulation::Simulation(Sea * seaSimulation)
{
    this->seaSimulation = seaSimulation ;
}

void Simulation::run()
{
    qDebug() << "Function run" ;
    runSimulation();

    // Sleep between turns
    QThread::msleep(1000);

}

void Simulation::runSimulation()
{
    unsigned int currentTurn=0 ;
    unsigned int x=0 ;
    unsigned int y=0 ;
    Animal * currentAnimal ;

    qDebug() << "Start Simulation" ;
    // Loop for the turns
    for(currentTurn=0; currentTurn< this->seaSimulation->getSimulationTurns() ; currentTurn++)
    {
        qDebug() << "Turn " << currentTurn ;
        qDebug() << "Sharks turn" ;

        // Shark turns
        for(x=0 ; x<this->seaSimulation->getWidth() ; x++)
        {
            for(y=0 ; y<this->seaSimulation->getHeight() ; y++)
            {
                currentAnimal = this->seaSimulation->Get(x, y) ;

                // if it's a shark
                if(currentAnimal != NULL)
                {
                    if(currentAnimal->GetType() == SHARK)
                    {
                        qDebug() << "Move shark at "<< currentAnimal->getX() << " " << currentAnimal->getY() ;
                        currentAnimal->Move();
                    }
                }
            }
        }

        qDebug() << "Fishes turn" ;
        // Fishes turns
        for(x=0 ; x<this->seaSimulation->getWidth() ; x++)
        {
            for(y=0 ; y<this->seaSimulation->getHeight() ; y++)
            {
                currentAnimal = this->seaSimulation->Get(x, y) ;

                // if it's a fish
                if(currentAnimal != NULL && currentAnimal->GetType() == FISH)
                {
                    currentAnimal->Move();
                }
            }
        }
    }
    qDebug() << "End Simulation" ;
}
