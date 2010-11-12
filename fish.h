#ifndef FISH_H
#define FISH_H

#include "animal.h"

#define FISH 1

class Fish : public Animal
{
public:

    Fish();
    Fish(int x, int y);
    inline void Eaten() {this->life = 0;}
    void Move();
    void Procreate(int x, int y);
    static void InitVars(int maxLife, int reproductionCycle, int decayTime, int matureTime);
    inline int MaxLife() {return MAX_LIFE;}
    inline int MatureTime() {return MATURE_TIME;}
    inline int Starvation() {return 1;}
    inline int GetType() {return FISH;}

private:
    static int MAX_LIFE;
    static int REPRODUCTION_CYCLE;
    static int DECAY_TIME;
    static int MATURE_TIME;
};

#endif // FISH_H
