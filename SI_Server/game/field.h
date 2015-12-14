#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "player.h"
#include "enemy.h"
#include "gameobject.h"

typedef struct Field {
    Player players[2];
    Enemy enemies[30];
    GameObject objects[1000]; // bullets, etc..
} Field;

#endif // GAME_FIELD_H
