#ifndef ANIMAL_H
#define ANIMAL_H

#include "rand.h"
#include "sea.h"

class Animal
{
public:
    virtual void Move() = 0;
    virtual void Procreate() = 0;
    inline bool Alive() {return life > 0;}
    inline bool Mature() {return life < (this->MaxLife() - this->MatureTime());}
    inline unsigned int getX() {return posX;}
    inline unsigned int getY() {return posY;}
    inline static void setSea(Sea * _sea) {sea = _sea;}
    inline static bool issetSea() {return sea != NULL;}

protected:
    unsigned int posX;
    unsigned int posY;

    int life;
    unsigned int reproduction;

    virtual int MaxLife() = 0;
    virtual int MatureTime() = 0;
    virtual int Starvation() = 0;
    static Sea * sea;
};

#endif // ANIMAL_H
