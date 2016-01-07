#ifndef NETWORK_NET_H
#define NETWORK_NET_H
#include <stdint.h>
#include "../util/queue.h"
#include "../game/field.h"

#define MAX_CONNECTIONS 2

typedef enum {CONNECTED, DISCONNECTED} net_state;
typedef enum {RUNNING, SHUTDOWN} net_server_state;
net_state net_status;
net_server_state net_server_status;

typedef struct net_client_descr_t {
    int socket;
    struct Queue *send;
} net_client_descr_t;

int net_socket, net_new_socket, net_c, clients_count;
Field* net_field;

int net_port_bind(uint16_t port);
int net_server_start(uint16_t port);
void *net_server_receive(void *);
void *net_server_send(void *);
void *net_game_thread(net_client_descr_t *);
void sigpipe_handler();

#endif // NETWORK_NET_H
