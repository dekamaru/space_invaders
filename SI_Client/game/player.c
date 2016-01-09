//
// Created by dekamaru on 05.01.16.
//

#include <stdlib.h>
#include <SDL2/SDL_rect.h>
#include "player.h"
#include "../engine/engine.h"

void player_update(Player *p, int x, int y, int health, int score) {
    p->x = x;
    p->y = y;
    p->health = health;
    p->score = score;
}

void player_render(Player *p) {
    SDL_Rect player;
    player.x = p->x;
    player.y = p->y;
    player.w = p->width;
    player.h = p->height;
    SDL_RenderCopy(renderer, assets_bundle->images[0], NULL, &player);
}

Player* player_create() {
    Player* p = malloc(sizeof(Player));
    p->width = 32;
    p->height = 32;
    return p;
}
