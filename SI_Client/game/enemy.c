#include <stdlib.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "enemy.h"
#include "../engine/engine.h"

Enemy* enemy_create(int x, int y, int type, int health) {
    Enemy *e = malloc(sizeof(Enemy));
    e->x = x;
    e->y = y;
    e->type = type;
    e->health = health;
    e->width = 32;
    e->height = 32;
    e->type = 0;
    return e;
}

void enemy_render(Enemy *e) {
    SDL_Rect enemy;
    enemy.x = e->x;
    enemy.y = e->y;
    enemy.w = e->width;
    enemy.h = e->height;
    SDL_Color b = {0, 0, 0, 255};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &enemy);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
