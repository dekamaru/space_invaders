#include "network/net.h"
#include "game/field.h"
#include <time.h>


int main(int *argc, char **argv)
{
    net_server_start(27015);
    return 0;
}
