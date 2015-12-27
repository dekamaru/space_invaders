#include "network/net.h"
#include "game/field.h"
#include <time.h>

int* test() {
    int *a = malloc(sizeof(int) * 4);
    a[0] = 311;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    return a;
}

int main(int *argc, char **argv)
{

    int *a = test();
    printf("%i", (*a + 4));
    //net_server_start(27015);
    return 0;
}
