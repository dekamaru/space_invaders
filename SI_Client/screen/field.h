#ifndef SI_CLIENT_FIELD_H
#define SI_CLIENT_FIELD_H

#include <SDL_rect.h>
#include "../game/player.h"
#include "../game/enemy.h"
#include "../game/gameobject.h"
#include "../engine/network.h"

#define MAX_PLAYERS 2
#define MAX_ENEMIES 30
#define MAX_OBJECTS 100

typedef struct Field {
    Player players[MAX_PLAYERS];
    Enemy enemies[MAX_ENEMIES];
    GameObject objects[MAX_OBJECTS]; // bullets, etc..
} Field;

void field_init();
void field_draw(void *renderer);
void field_event(void *event);
void field_update();
void* receiver_thread();
void field_parse_packet(char* data);

int score;

#endif //SI_CLIENT_FIELD_H
