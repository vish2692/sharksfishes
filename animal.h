#ifndef ANIMAL_H
#define ANIMAL_H

#include "rand.h"
#include "sea.h"
#include "animals.h"

class Animal
{
public:
    virtual void Move() = 0;
    virtual void Procreate(int x, int y) = 0;
    inline bool Alive() {return life > 0;}
    inline bool Mature() {return life < (this->MaxLife() - this->MatureTime());}
    inline unsigned int getX() {return posX;}
    inline unsigned int getY() {return posY;}
    inline void setX(unsigned int x) {posX = x;}
    inline void setY(unsigned int y) {posY = y;}
    inline static void setSea(Sea * _sea) {sea = _sea;}
    inline static bool issetSea() {return sea != NULL;}
    virtual int GetType() = 0;

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
