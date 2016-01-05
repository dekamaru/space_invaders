//
// Created by dekamaru on 05.01.16.
//

#include <stdlib.h>
#include <SDL2/SDL_rect.h>
#include "player.h"
#include "../engine/engine.h"

Player *player_load(int x, int y, int lives, int score) {
    Player* p = malloc(sizeof(Player));
    p->x = x;
    p->y = y;
    p->lives = lives;
    p->score = score;
    p->width = 32;
    p->height = 32;
    return p;
}

void player_render(Player *p) {
    SDL_Rect player;
    player.x = p->x;
    player.y = p->y;
    player.w = p->width;
    player.h = p->height;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &player);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}