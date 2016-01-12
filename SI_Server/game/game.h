#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "player.h"
#include "enemy.h"
#include "gameobject.h"
#include "field.h"

#define WORLD_WIDTH 640
#define WORLD_HEIGHT 480
#define MAX_SPAWNED_ENEMIES 10
#define ENEMY_SPAWN_CHANCE 50
#define ENEMY_SHOOT_CHANCE 100


#define HEALTH_PACK_CHANCE 10
#define HEALTH_PACK_GAIN 50

void game_init(Field* field); // field
void game_packet_handle(int packet_id, char* packet_data, Field *f);
void game_update(Field* field);

void game_update_gameobjects(Field* field);
void game_update_enemies(Field* field);


#endif // GAME_GAME_H
