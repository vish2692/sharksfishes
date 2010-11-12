#ifndef FISH_H
#define FISH_H

#include "animal.h"

class Fish : public Animal
{
public:

    Fish();
    Fish(Fish * parent);
    inline void Eaten() {this->life = 0;}
    void Move();
    void Procreate();
    static void InitVars(int maxLife, int reproductionCycle, int decayTime, int matureTime);
    inline int MaxLife() {return MAX_LIFE;}
    inline int MatureTime() {return MATURE_TIME;}
    inline int Starvation() {return 1;}

private:
    static int MAX_LIFE;
    static int REPRODUCTION_CYCLE;
    static int DECAY_TIME;
    static int MATURE_TIME;
};

#endif // FISH_H
