#include <stdio.h>
#include "util/queue.h"

//TODO: сделать прослойку серверную, на сервере игровой луп, в неём вся логика, клиент только отображение
// СЕРВЕР: два потока

// pthreads, сокеты, очереди
// сначала сервер делать, использовать telnet


int main(int *argc, char **argv)
{
    struct Queue* q = queue_create();

    return 0;
}
