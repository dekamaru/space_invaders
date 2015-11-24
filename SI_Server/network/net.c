#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include "net.h"
#include "../util/endian.h"

#define MAX_CONNECTIONS 2

struct sockaddr_in net_server, net_client;

int net_port_bind(int port) {
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (net_socket == -1) {
        puts("net_port_bind(): socket creating fail!");
        return 0;
    }
    net_server.sin_family = AF_INET;
    net_server.sin_addr.s_addr = INADDR_ANY;
    net_server.sin_port = htons(port);
    if (bind(net_socket, (struct sockaddr*)&net_server, sizeof(net_server)) < 0) {
        return 0;
    }
    return 1;
}

int net_server_start(int port) {
    if (net_port_bind(port) == 0) {
        puts("net_server_start(): bind fail!");
        return 0;
    }
    puts("net_server_start(): binding success");

    listen(net_socket, MAX_CONNECTIONS);
    while((net_new_socket = accept(net_socket, (struct sockaddr*)&net_client, (socklen_t*)&net_c))) {
        pthread_t net_sniffer_thread;
        net_new_sock = malloc(1);
        *net_new_sock = net_new_socket;
        // pre init()?
        if(pthread_create(&net_sniffer_thread, NULL, net_connection_handler, (void*) net_new_sock) < 0) {
            puts("net_server_start(): could not create thread");
        }
    }
}

int net_client_connect(char* addr, int port) {
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (net_socket == -1) {
        puts("net_client_connect(): socket creating fail!");
        return 0;
    }
    net_server.sin_addr.s_addr = inet_addr(addr);
    net_server.sin_family = AF_INET;
    net_server.sin_port = htons(port);
    if(connect(net_socket, (struct sockaddr *)&net_server, sizeof(net_server)) < 0) {
        puts("net_client_connect(): connection failed");
        return 0;
    }
    return 1;
}

int net_client_receive(char* buffer) {
    return recv(net_socket, buffer, 2000, 0) > 0;
}

int net_client_send(char* message, int length) {
    return send(net_socket, message, length, 0) > 0;
}

void *net_connection_handler(void *socket_desc) {
    int sock = *(int*)socket_desc;
    char *message;
    char client_reply[2000];
    message = "Message of the day: hello!";
    write(sock, message, strlen(message));

    while(recv(sock, client_reply, 2000, 0) > 0) {
        puts(client_reply);
    }

    free(socket_desc);
    return 0;
}



