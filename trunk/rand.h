#ifndef RAND_H
#define RAND_H

#include <stdlib.h>
#include <time.h>
#include "randexception.h"

class Rand
{
public:
    Rand();
    int next(int max) throw RandException;
    int next(int min, int max) throw RandException;
};

#endif // RAND_H
