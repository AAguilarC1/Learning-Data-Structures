#ifndef TEST_UTIL_H
#define TEST_UTIL_H
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

inline int test_random_int(int upper, int lower){
    return (rand() % (upper - lower + 1)) + lower;
}

#endif // TEST_UTIL_H

