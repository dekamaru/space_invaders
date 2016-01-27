#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include "time.h"

uint32_t time_get_tick() {
    struct timeval t;
    uint32_t tick;
    gettimeofday(&t, NULL);
    tick = t.tv_sec + (t.tv_usec / 1000000.0);
    return tick;
}

uint32_t rand_between(uint32_t start, uint32_t end) {
    uint32_t range = 1 + end - start;
    uint32_t limit = RAND_MAX - (RAND_MAX % range);

    uint32_t rand_value;
    do {
        rand_value = rand();
    } while (rand_value >= limit);

    return (rand_value % range) + start;
}
