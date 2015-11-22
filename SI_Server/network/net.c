#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "net.h"
#include "../util/endian.h"

struct sockaddr_in net_server, net_client;

int net_port_bind() {
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (net_socket == -1) {
        return 0;
    }
    net_server.sin_family = AF_INET;
    net_server.sin_addr.s_addr = INADDR_ANY;
    net_server.sin_port = htons(net_port);
    if (bind(net_socket, (struct sockaddr*)&net_server, sizeof(net_server)) < 0) {
        return 0;
    }
    return 1;
}

int net_server_start(int port) {
    net_port = port;
    if (net_port_bind() == 0) {
        return 0; // logger?
    }

    listen(net_socket, 3);
    while((net_new_socket = accept(net_socket, (struct sockaddr*)&net_client, (socklen_t*)&net_c))) {
        net_server_loop(net_new_socket);
    }
}

void net_server_loop(int n_socket) {
    write(n_socket, "hello world", 11);
}




