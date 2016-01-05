//
// Created by dekamaru on 04.01.16.
//

#ifndef SI_CLIENT_GAME_H
#define SI_CLIENT_GAME_H

#include "../engine/assets.h"
#include "../engine/screen.h"

void game_init();
void game_draw(void* renderer);
void game_event(void* event);
void game_update();
void game_wait_start();

int client_id;

#endif //SI_CLIENT_GAME_H
