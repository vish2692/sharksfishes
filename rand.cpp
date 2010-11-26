#include "rand.h"

Rand::Rand()
{
    srand(time(NULL));
}

int Rand::next(int max) {
    if(max < 1) return 0 ;
    return rand() % max;
}

int Rand::next(int min, int max) {
    if((max-min) < 1) return 0 ;
    return rand() % (max-min) + min;
}
