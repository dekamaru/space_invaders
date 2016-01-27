#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "packet.h"
#include "net.h"

#include "../game/game.h"
#include "packer.h"
#include "../util/time.h"

net_server_state net_server_status; // needed global var!

int net_port_bind(uint16_t port) {
    struct sockaddr_in net_server;
    int net_socket;
    const int yes = 1;

    net_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (net_socket == -1) {
        fprintf(stderr, "net_port_bind(): socket creating fail!\n");
        return 0;
    }
    net_server.sin_family = AF_INET;
    net_server.sin_addr.s_addr = INADDR_ANY;
    net_server.sin_port = htons(port);
    setsockopt(net_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (bind(net_socket, (struct sockaddr*)&net_server, sizeof(net_server)) < 0) {
        return 0;
    }
    return net_socket;
}

int net_server_start(uint16_t port) {
    int net_socket = net_port_bind(port);
    net_client_descr_t clients[MAX_CONNECTIONS];
    struct sockaddr_in net_client;
    int clients_count = 0;
    int net_new_socket = 0, net_c = 0;

    if (net_socket == 0) {
        fprintf(stderr, "[Server] Bind failed on port %i\n", port);
        return 0;
    }
    fprintf(stdout, "[Server] Binding success on port %i\n", port);

    listen(net_socket, MAX_CONNECTIONS);
    while((net_new_socket = accept(net_socket, (struct sockaddr*)&net_client, (socklen_t*)&net_c)) && clients_count < MAX_CONNECTIONS) {
        pthread_t net_receive_thread, net_send_thread;

        clients[clients_count].socket = net_new_socket;
        clients[clients_count].send = queue_create();

        // sending client his id
        const char* handshake = packet_create_handshake(clients_count);
        send(net_new_socket, handshake, sizeof(Packet) + 1, 0);

        fprintf(stdout, "[Server] Client connected.\n");

        pthread_create(&net_receive_thread, NULL, (void *(*)(void *)) net_server_receive, (void*) &clients[clients_count]);
        pthread_create(&net_send_thread, NULL, (void *(*)(void *)) net_server_send, (void*) &clients[clients_count]);
        if (clients_count == MAX_CONNECTIONS - 1) break;
        clients_count++;
    }
    pthread_t game_thread;
    pthread_create(&game_thread, NULL, (void *(*)(void *)) net_game_thread, clients);
    net_server_status = RUNNING;

    pthread_join(game_thread, NULL); //waiting the game shutdown
    return 0;
}

void net_game_thread(net_client_descr_t *clients) {
    Field *net_field = malloc(sizeof(Field));
    char* field_buffer = malloc(512);

    game_init(net_field);

    for(int i = 0; i < MAX_CONNECTIONS; i++) {
        // sending packet 2 (game start)
        Packet *p = (Packet*) packet_create(2, 1, "1");
        queue_push(clients[i].send, p);
        clients[i].field = net_field;
    }
    
    while(net_server_status != SHUTDOWN) {
        game_update(net_field);

        int game_over = 1;
        for(int i = 0; i < MAX_CONNECTIONS; i++) {
            if (!net_field->players[i].is_dead) game_over = 0;
        }
        if (game_over) {
            Packet* p = (Packet *) packet_create(8, 1, "1");
            for(int i = 0; i < MAX_CONNECTIONS; i++) queue_push(clients[i].send, p);
            net_server_status = SHUTDOWN;
            break;
        }

        packer_pack_field(field_buffer, net_field);
        Packet* p = (Packet*) packet_create(3, strlen(field_buffer), field_buffer);
        for(int i = 0; i < MAX_CONNECTIONS; i++) queue_push(clients[i].send, p);
        usleep(30000);
    }
}

void net_server_receive(void* args) {
    net_client_descr_t *arguments = (net_client_descr_t*) args;
    const int sock = arguments->socket;
    char* client_reply = malloc(512);
    while(recv(sock, client_reply, sizeof(Packet), 0) > 0) {
        char* buffer = malloc(512);
        memcpy(buffer, client_reply, sizeof(Packet));
        Packet* p = (Packet*) buffer;
        if (p->data_length != 0) {
            char* received_data = malloc(p->data_length + 1);
            recv(sock, received_data, p->data_length, 0);
            received_data[p->data_length] = 0;
            strcpy(p->data, received_data);
            free(received_data);
            if (arguments->field != NULL) game_packet_handle(p->packet_id, p->data, arguments->field);
        }
    }
    close(arguments->socket);
}

void net_server_send(void* args) {
    net_client_descr_t *arguments = (net_client_descr_t*) args;
    while(net_server_status != SHUTDOWN) {
        if (!queue_empty(arguments->send)) {
            Packet *p = queue_pop(arguments->send);
            if (p != NULL) {
                char *buffer;
                buffer = (char*) p;
                send(arguments->socket, buffer, sizeof(Packet) + p->data_length, 0);
            }
        }
    }
}