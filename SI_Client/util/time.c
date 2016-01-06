#include <stddef.h>
#include <sys/time.h>
#include "time.h"

unsigned long time_get_tick() {
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0) return 0;
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
