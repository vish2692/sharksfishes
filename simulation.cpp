#include "simulation.h"
#include "animal.h"
#include "shark.h"
#include "fish.h"
#include <QDebug>
#include <QList>
#include <QFile>
#include <QTextStream>

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
    QFile stats("Statistiques");
    if (!stats.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier de statistiques.";
        return;
    }
    QTextStream out(&stats);
    unsigned int currentTurn=0 ;
    unsigned int x=0 ;
    unsigned int y=0 ;

    unsigned int currentSharksNumber = 0 ;
    unsigned int currentFishesNumber = 0 ;

    unsigned int turnStartingSharksNumber = 0 ;
    unsigned int turnStartingFishesNumber = 0 ;

    Animal * currentAnimal ;

    this->seaSimulation->Init();
    this->seaSimulation->Populate();

    qDebug() << "Start Simulation" ;
    // Loop for the turns
    for(currentTurn=0; currentTurn< this->seaSimulation->getSimulationTurns() ; currentTurn++)
    {
        turnStartingSharksNumber = 0;
        turnStartingFishesNumber = 0;
        // Recuperation of all the sharks
        QList<Shark *> sharksToMove = QList<Shark *>() ;
        for(x=0 ; x<this->seaSimulation->getWidth() ; x++)
        {
            for(y=0 ; y<this->seaSimulation->getHeight() ; y++)
            {
                currentAnimal = this->seaSimulation->Get(x, y) ;

                if(currentAnimal != NULL) {
                    if(currentAnimal->GetType() == SHARK) {
                        sharksToMove.append((Shark*)currentAnimal);
                        turnStartingSharksNumber++;
                    }
                    else
                        turnStartingFishesNumber++;
                }
            }
        }
        currentSharksNumber = sharksToMove.length() ;

        qDebug() << "Starting Sharks : " << turnStartingSharksNumber;
        qDebug() << "Starting Fishes : " << turnStartingFishesNumber;
        out << "Sharks : " << turnStartingSharksNumber << " Fishes : " << turnStartingFishesNumber << endl;

        // Shark turns
        qDebug() << "Sharks turn to move : " << currentSharksNumber ;
        while(!sharksToMove.isEmpty())
        {
            currentAnimal = sharksToMove.takeFirst();
            currentAnimal->Move();
        }

        // Recuperation of all the fishes
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

        if(currentSharksNumber == 0 && currentFishesNumber == 0 )
        {
            qDebug() << "No more animals, simulation stopped at turn "<<currentTurn ;
            break ;
        }
    }
    qDebug() << "End Simulation" ;
}
