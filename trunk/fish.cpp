#include "fish.h"
#include <QDebug>

int Fish::MAX_LIFE;
int Fish::REPRODUCTION_CYCLE;
int Fish::DECAY_TIME;
int Fish::MATURE_TIME;

Fish::Fish() {
    Rand rand = Rand();

    this->life = MAX_LIFE - rand.next(MAX_LIFE);
    this->reproduction = rand.next(REPRODUCTION_CYCLE);

    do {
        this->posX = rand.next(Animal::sea->getWidth());
        this->posY = rand.next(Animal::sea->getHeight());
    }while(Animal::sea->Get(this->posX, this->posY) != NULL);

    Animal::sea->Set(this->posX, this->posY, this);
    qDebug() << "Fish created" ;
}

Fish::Fish(int x, int y) {
    Rand rand = Rand();
    this->life = MAX_LIFE;
    this->reproduction = rand.next(REPRODUCTION_CYCLE);
    this->posX = x;
    this->posY = y;

    Animal::sea->Set(this->posX, this->posY, this);
    qDebug() << "Fish created at pos "<< this->posX << " " << this->posY ;
}

void Fish::InitVars(int maxLife, int reproductionCycle, int decayTime, int matureTime) {
    MAX_LIFE = maxLife;
    REPRODUCTION_CYCLE = reproductionCycle;
    DECAY_TIME = decayTime;
    MATURE_TIME = matureTime;
}

void Fish::Move() {
    //Life left :
    if(--life < 1)
    {
        qDebug() << "A fish died pos "<< this->posX << " " << this->posY ;
        if(life + DECAY_TIME < 0) {
            Animal::sea->Delete(this);
        }
        return;
    }

    Rand rand = Rand();
    int baseX = 0;
    int baseY = 0;
    while(baseX == 0 && baseY == 0) {
        baseX = rand.next(3);
        baseY = rand.next(3);
    }
    int currentX = baseX;
    int currentY = baseY;
    bool ok = false;
    int checkedCell = 0 ;

    do {
        if(Animal::sea->Get(this->posX + currentX - 1, this->posY + currentY - 1) == NULL) {
            ok = true;
        }
        else {
            if(currentX < 2)
                currentX += (currentY == 1 ? 2 : 1);
            else if(currentY < 2) {
                currentX = 0;
                currentY++;
            }
            else {
                currentX = 0;
                currentY = 0;
            }
        }
        checkedCell++ ;
    }while((currentX != baseX || currentY != baseY) && !ok && checkedCell < 8);

    // management of procreation.
    this->reproduction--;
    if(ok) {
        if(reproduction < 1) {
            this->Procreate(this->posX, this->posY);
        }
        Animal::sea->Move(this, this->posX + currentX - 1, this->posY + currentY - 1);
    }
}

void Fish::Procreate(int x, int y) {
    new Fish(x, y);
    this->reproduction = REPRODUCTION_CYCLE;
}
