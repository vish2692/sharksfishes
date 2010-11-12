#ifndef SHARK_H
#define SHARK_H

#include "animal.h"

class Shark : public Animal
{
public:
    Shark();
    inline static void InitVars(int maxLife, int reproductionCycle, int decayTime, int matureTime) {
        MAX_LIFE = maxLife;
        REPRODUCTION_CYCLE = reproductionCycle;
        DECAY_TIME = decayTime;
        MATURE_TIME = matureTime;
    }
    inline int MaxLife() {return MAX_LIFE;}
    inline int MatureTime() {return MATURE_TIME;}
    inline int Starvation() {return starvation;}

private:
    void LookForFish();

    unsigned int starvation;

    static int MAX_LIFE;
    static int REPRODUCTION_CYCLE;
    static int DECAY_TIME;
    static int MATURE_TIME;
    static int STARVATION_TIME;
};

#endif // SHARK_H
