#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "network/net.h"

int main(int argc, char **argv)
{
    int port = DEFAULT_PORT;
    if (argc == 2) port = atoi(argv[1]);
    srand((unsigned int) time(NULL));
    net_server_start(port);
    return 0;
}
