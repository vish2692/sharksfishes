#ifndef SHARK_H
#define SHARK_H

#include "animal.h"

class Shark : public Animal
{
public:
    Shark();
    Shark(int x, int y);
    void Move();
    void Procreate(int x, int y);
    static void InitVars(int maxLife, int reproductionCycle, int decayTime, int matureTime, int starvationTime);
    inline int MaxLife() {return MAX_LIFE;}
    inline int MatureTime() {return MATURE_TIME;}
    inline int Starvation() {return starvation;}
    inline int GetType() {return SHARK;}

private:
    void LookForFish();

    int starvation;

    static int MAX_LIFE;
    static int REPRODUCTION_CYCLE;
    static int DECAY_TIME;
    static int MATURE_TIME;
    static int STARVATION_TIME;
};

#endif // SHARK_H
