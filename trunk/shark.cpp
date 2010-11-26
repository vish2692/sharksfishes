#include "shark.h"
#include "fish.h"
#include <QDebug>

int Shark::MAX_LIFE;
int Shark::REPRODUCTION_CYCLE;
int Shark::DECAY_TIME;
int Shark::MATURE_TIME;
int Shark::STARVATION_TIME;

Shark::Shark() {
    Rand rand = Rand();
    this->life = MAX_LIFE - rand.next(MAX_LIFE);
    this->reproduction = rand.next(REPRODUCTION_CYCLE);
    this->starvation = rand.next(STARVATION_TIME);

    do {
        this->posX = rand.next(Animal::sea->getWidth());
        this->posY = rand.next(Animal::sea->getHeight());
    }while(Animal::sea->Get(this->posX, this->posY) != NULL);

    Animal::sea->Set(this->posX, this->posY, this);
    qDebug() << "Shark created" ;
}

Shark::Shark(int x, int y) {
    Rand rand = Rand();
    this->life = MAX_LIFE;
    this->reproduction = rand.next(REPRODUCTION_CYCLE);
    this->starvation = rand.next(STARVATION_TIME);
    this->posX = x;
    this->posY = y;

    Animal::sea->Set(this->posX, this->posY, this);
    qDebug() << "Shark created at pos "<< this->posX << " " << this->posY ;
}

void Shark::InitVars(int maxLife, int reproductionCycle, int decayTime, int matureTime, int starvationTime) {
    MAX_LIFE = maxLife;
    REPRODUCTION_CYCLE = reproductionCycle;
    DECAY_TIME = decayTime;
    MATURE_TIME = matureTime;
    STARVATION_TIME = starvationTime ;
}

void Shark::Move() {
    //Life left :
    if(--life < 1)
    {
        qDebug() << "A shark died pos "<< this->posX << " " << this->posY ;
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
    int okX = this->posX;
    int okY = this->posY;
    bool ok = false;
    bool eat = false;
    int checkedCell = 0 ;

    Animal * target = NULL;
    do {
        target = Animal::sea->Get(this->posX + currentX - 1, this->posY + currentY - 1);
        if(!ok && target == NULL) {
            okX = this->posX + currentX - 1;
            okY = this->posY + currentY - 1;
            ok = true;
        }
        else if(target != NULL && target->GetType() == FISH) {
            okX = this->posX + currentX - 1;
            okY = this->posY + currentY - 1;
            ok = true;
            eat = true;
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
    }while((currentX != baseX || currentY != baseY) && !eat && checkedCell < 8);

    // management of procreation and starvation.
    this->reproduction--;
    this->starvation--;
    if(ok) {
        if(reproduction < 1) {
            this->Procreate(this->posX, this->posY);
        }
        if(eat) {
            ((Fish*)target)->Eaten();
            this->starvation = this->STARVATION_TIME;
        }
        Animal::sea->Move(this, this->posX + currentX - 1, this->posY + currentY - 1);
    }
    if(starvation < 0) {
        qDebug() << "Shark starves" ;
        life = 0 ;
    }
}

void Shark::Procreate(int x, int y) {
    new Shark(x, y);
    this->reproduction = REPRODUCTION_CYCLE;
}
