#include <stdlib.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include "enemy.h"
#include "../engine/engine.h"

void enemy_update(Enemy *e, int x, int y, int type, int health) {
    e->x = x;
    e->y = y;
    e->type = type;
    e->health = health;
}

void enemy_render(Enemy *e, SDL_Rect *bounds) {
    bounds->x = e->x;
    bounds->y = e->y;
    bounds->w = e->width;
    bounds->h = e->height;
    SDL_RenderCopy(renderer, assets_bundle->images[3], NULL, bounds);
}

void enemy_dump(Enemy* e, int x, int y, int type, int health, int alive) {
    e->width = 32;
    e->height = 32;
    e->type = 0;
    e->x = x;
    e->y = y;
    e->type = type;
    e->health = health;
    e->alive = alive;
}
