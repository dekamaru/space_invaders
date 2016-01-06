#ifndef SI_CLIENT_FIELD_H
#define SI_CLIENT_FIELD_H

#include "../game/player.h"
#include "../util/queue.h"

#define MAX_PLAYERS 2

void field_init();
void field_draw(void *renderer);
void field_event(void *event);
void field_update();
void receiver_thread();
void sender_thread();

void field_resolve_data(int id, int a1, int a2, int a3, int a4);
void field_parse_packet(char* packet);

Player *players[MAX_PLAYERS];
int players_count, started;
Queue* packets_send;

#endif //SI_CLIENT_FIELD_H
