#ifndef RAND_H
#define RAND_H

#include <stdlib.h>
#include <time.h>

class Rand
{
public:
    Rand();
    int next(int max);
    int next(int min, int max);
};

#endif // RAND_H
