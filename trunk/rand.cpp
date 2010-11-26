#include "rand.h"

Rand::Rand()
{
    srand(time(NULL));
}

int Rand::next(int max) throw RandException {
    if(max == 0) throw new RandException("Invalid max : 0");
    return rand() % max;
}

int Rand::next(int min, int max) throw RandException {
    if((max - min) == 0) throw new RandException("Invalid parameters : max = min");
    return rand() % (max-min) + min;
}
