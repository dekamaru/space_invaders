#include "enemy.h"
#include "game.h"
#include "../util/time.h"
#include <time.h>
#include <stdlib.h>

void enemy_spawn(Enemy *e, int type, int x) {
    e->x = x;
    e->y = -10; // hiding from screen
    e->type = type;
    e->alive = 1;
    e->health = 100;
    e->speed = 2;
    e->width = e->height = 32;
}

void enemy_move(Enemy *e) {
    e->y += e->speed; // going down
}
