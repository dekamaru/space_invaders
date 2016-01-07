#include <stdlib.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "enemy.h"
#include "../engine/engine.h"

Enemy* enemy_create() {
    Enemy *e = malloc(sizeof(Enemy));
    e->width = 32;
    e->height = 32;
    e->type = 0;
    return e;
}

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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, bounds);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

Enemy *enemy_dump(int x, int y, int type, int health) {
    Enemy *e = malloc(sizeof(Enemy));
    e->width = 32;
    e->height = 32;
    e->type = 0;
    e->x = x;
    e->y = y;
    e->type = type;
    e->health = health;
    return e;
}
