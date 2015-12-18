#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "player.h"
#include "enemy.h"
#include "gameobject.h"
#include "field.h"

#define WORLD_WIDTH 640
#define WORLD_HEIGHT 480
#define MAX_SPAWNED_ENEMIES 10

void game_init(Field* field); // field
void game_packet_handle(int packet_id, char* packet_data, Field *f);
void game_update(Field* field);


#endif // GAME_GAME_H
