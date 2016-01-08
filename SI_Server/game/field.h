#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "player.h"
#include "enemy.h"
#include "gameobject.h"

#define MAX_PLAYERS 2
#define MAX_ENEMIES 30
#define MAX_OBJECTS 100

typedef struct Field {
    Player players[MAX_PLAYERS];
    Enemy enemies[MAX_ENEMIES];
    GameObject objects[MAX_OBJECTS]; // bullets, etc..
} Field;

int field_enemies_count(Field *f); // counting alive enemies
int field_enemies_find_space(Field *f); // get index of non-alive enemy
int field_gameobjects_find_space(Field *f);

#endif // GAME_FIELD_H
