#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "packet.h"
#include "net.h"
#include "../util/queue.h"

#include "../game/game.h"
#include "packer.h"
#include "../util/time.h"

struct sockaddr_in net_server, net_client;

int net_port_bind(uint16_t port) {
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

int net_server_start(uint16_t port) {
    if (net_port_bind(port) == 0) {
        puts("net_server_start(): bind fail!");
        return 0;
    }
    puts("net_server_start(): binding success");

    net_client_descr_t clients[MAX_CONNECTIONS];
    clients_count = 0;

    listen(net_socket, MAX_CONNECTIONS);
    while((net_new_socket = accept(net_socket, (struct sockaddr*)&net_client, (socklen_t*)&net_c)) && clients_count < MAX_CONNECTIONS) {
        pthread_t net_receive_thread, net_send_thread;

        clients[clients_count].socket = net_new_socket;
        clients[clients_count].send = queue_create();

        // sending client his id
        char* handshake = packet_create_handshake(clients_count);
        send(net_new_socket, handshake, sizeof(Packet) + 1, 0);

        printf("[Server] Client connected.\n");
        fflush(stdout);

        pthread_create(&net_receive_thread, NULL, net_server_receive, (void*) &clients[clients_count]);
        pthread_create(&net_send_thread, NULL, net_server_send, (void*) &clients[clients_count]);
        if (clients_count == MAX_CONNECTIONS - 1) break;
        clients_count++;
    }
    pthread_t game_thread;
    pthread_create(&game_thread, NULL, (void *(*)(void *)) net_game_thread, clients);
    net_server_status = RUNNING;

    pthread_join(game_thread, NULL); //waiting the game shutdown
}

int net_client_connect(char* addr, uint16_t port) {
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

void *net_game_thread(net_client_descr_t *clients) {
    net_field = malloc(sizeof(Field));
    char* field_buffer = malloc(512);
    game_init(net_field);

    // Limit loop to 30 fps
    const int FRAMES_PER_SECOND = 30;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
    unsigned long next_game_tick = time_get_tick();
    unsigned long sleep_time = 0;

    for(int i = 0; i < MAX_CONNECTIONS; i++) {
        // sending packet 2 (game start)
        Packet *p = (Packet*) packet_create(2, 1, "1");
        queue_push(clients[i].send, p);
    }
    
    while(net_server_status != SHUTDOWN) {
        game_update(net_field);
        packer_pack_field(field_buffer, net_field);
        Packet* p = (Packet*) packet_create(3, strlen(field_buffer), field_buffer);
        for(int i = 0; i < MAX_CONNECTIONS; i++) queue_push(clients[i].send, p);

        // Limiting loop
        next_game_tick += SKIP_TICKS;
        sleep_time = next_game_tick - time_get_tick();
        if(sleep_time >= 0) {
            usleep(sleep_time);
        }
    }
}

void *net_server_receive(void* args) {
    net_client_descr_t *arguments = (net_client_descr_t*) args;
    int sock = arguments->socket;
    char* client_reply = malloc(512);
    while(recv(sock, client_reply, sizeof(Packet), 0) > 0) {
        char* buffer = malloc(512);
        memcpy(buffer, client_reply, sizeof(Packet));
        Packet* p = (Packet*) buffer;
        if (p->data_length != 0) {
            char* received_data = malloc(p->data_length);
            recv(sock, received_data, p->data_length, 0);
            strcpy(p->data, received_data);
            free(received_data);
            if (net_field != NULL) game_packet_handle(p->packet_id, p->data, net_field);
        }
    }
    if (clients_count == 1) {
        clients_count--;
    }
    shutdown(arguments->socket, 2);
    return 0;
}

void *net_server_send(void* args) {
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
