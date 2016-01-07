#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "network/net.h"

void command_input_handler() {
    char command[1024];
    printf("Server have commands. Type help to see them\n");
    while(1) {
        scanf("%s", &command);
        if (strcmp(command, "shutdown") == 0) {
            close(net_socket);
            exit(0);
        }
    }
}

int main(int *argc, char **argv)
{
    pthread_t command_input;
    pthread_create(&command_input, NULL, command_input_handler, NULL);
    net_server_start(26001);
    return 0;
}
