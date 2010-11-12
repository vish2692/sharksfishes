#include "rand.h"

Rand::Rand()
{
    srand(time(NULL));
}

int Rand::next(int max) {
    return rand() % max;
}

int Rand::next(int min, int max) {
    return rand() % (max-min) + min;
}
