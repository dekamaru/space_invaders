#include <stdio.h>
#include "util/queue.h"
#include "util/endian.h"
#include "network/net.h"

//TODO: сделать прослойку серверную, на сервере игровой луп, в неём вся логика, клиент только отображение
// СЕРВЕР: два потока

// pthreads, сокеты, очереди
// сначала сервер делать, использовать telnet


typedef struct tPack {
    int value;
} tPack;

int main(int *argc, char **argv)
{
    net_server_start(27015);
    return 0;
}
