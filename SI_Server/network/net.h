#ifndef NETWORK_NET_H
#define NETWORK_NET_H
#include <stdint.h>
#include "../util/queue.h"
#include "../game/field.h"

#define MAX_CONNECTIONS 2
#define DEFAULT_PORT 26000

typedef enum {RUNNING, SHUTDOWN} net_server_state;
typedef struct net_client_descr_t {
    int socket;
    struct Queue *send;
    struct Field *field;
} net_client_descr_t;

int net_port_bind(uint16_t port);
int net_server_start(uint16_t port);
void net_server_receive(void *);
void net_server_send(void *);
void net_game_thread(net_client_descr_t *);

#endif // NETWORK_NET_H
