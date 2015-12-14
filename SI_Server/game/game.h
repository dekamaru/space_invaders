#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "player.h"
#include "enemy.h"
#include "gameobject.h"
#include "field.h"

void game_init(Field* field); // field
void game_packet_handle(int packet_id, char* packet_data, Field *f);

#endif // GAME_GAME_H
