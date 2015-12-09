#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include "packet.h"
#include "net.h"
#include "../util/queue.h"

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

    Queue* receive = queue_create();
    net_client_descr_t clients[MAX_CONNECTIONS];
    int clients_count = 0;

    listen(net_socket, MAX_CONNECTIONS);
    while((net_new_socket = accept(net_socket, (struct sockaddr*)&net_client, (socklen_t*)&net_c)) && clients_count < MAX_CONNECTIONS) {
        pthread_t net_receive_thread, net_send_thread;
        clients[clients_count].receive = receive;
        clients[clients_count].send = queue_create();

        net_new_sock = malloc(1);
        *net_new_sock = net_new_socket;
        clients[clients_count].socket = net_new_sock;

        pthread_create(&net_receive_thread, NULL, net_server_receive, (void*) &clients[clients_count]);
        pthread_create(&net_send_thread, NULL, net_server_send, (void*) &clients[clients_count]);
        if (clients_count == MAX_CONNECTIONS - 1) break;
        clients_count++;
    }
    pthread_t game_thread;
    pthread_create(&game_thread, NULL, net_game_thread, clients);
    net_server_status = RUNNING;

    while(net_server_status == RUNNING) {} // sleeeeeeeeeep
}

int net_client_connect(char* addr, int port) {
    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (net_socket == -1) {
        puts("net_client_connect(): socket creating fail!");
        net_status = DISCONNECTED;
        return 0;
    }
    net_server.sin_addr.s_addr = inet_addr(addr);
    net_server.sin_family = AF_INET;
    net_server.sin_port = htons(port);
    if(connect(net_socket, (struct sockaddr *)&net_server, sizeof(net_server)) < 0) {
        puts("net_client_connect(): connection failed");
        net_status = DISCONNECTED;
        return 0;
    }
    net_status = CONNECTED;
    return 1;
}

int net_client_receive(char* buffer, int length) {
    return recv(net_socket, buffer, length, 0) > 0;
}

int net_client_send(char* message) {
    Packet* buffer = (Packet*) message;
    return send(net_socket, message, sizeof(Packet) + buffer->data_length, 0) > 0;
}

void *net_game_thread(net_client_descr_t *clients) {

    while(1) {
        Queue* receive = clients[0].receive;
        if (!queue_empty(receive)) {
            Packet *p = queue_pop(receive);
            free(p);
        }
        // send pppp
    }
}

void *net_server_receive(void* args) {
    net_client_descr_t *arguments = (net_client_descr_t*) args;
    int sock = *(int*) arguments->socket;
    char* client_reply = malloc(1024);
    while(recv(sock, client_reply, sizeof(Packet), 0) > 0) {
        Packet* p = (Packet*) client_reply;
        if (p->data_length != 0) {
            char* received_data = malloc(p->data_length);
            recv(sock, received_data, p->data_length, 0);
            strcpy(p->data, received_data);
            queue_push(arguments->receive, p);
        }
    }
    free(arguments->socket);
    return 0;
}

void *net_server_send(void* args) {
    net_client_descr_t *arguments = (net_client_descr_t*) args;
    while(1) {
        if (!queue_empty(arguments->send)) {
            Packet *p = queue_pop(arguments->send);
            printf("Sending packet id: %i\n", p->packet_id);
            free(p);
            fflush(stdout);
        }
    }
}
