//
// Created by dekamaru on 04.01.16.
//

#include <stdint.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"

int net_client_connect(char* addr, uint16_t port) {
    struct sockaddr_in net_server;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (net_socket == -1) {
        return 0;
    }
    net_server.sin_addr.s_addr = inet_addr(addr);
    net_server.sin_family = AF_INET;
    net_server.sin_port = htons(port);
    if(connect(net_socket, (struct sockaddr *)&net_server, sizeof(net_server)) < 0) {
        return 0;
    }
    return 1;
}

Packet *net_receive_packet() {
    char* server_reply = malloc(1024);
    if(recv(net_socket, server_reply, sizeof(Packet), 0) > 0) {
        Packet* p = (Packet*) server_reply;
        if (p->data_length != 0) {
            char* received_data = malloc(p->data_length);
            recv(net_socket, received_data, p->data_length, 0);
            received_data[p->data_length] = 0;
            strcpy(p->data, received_data);
            return p;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}
