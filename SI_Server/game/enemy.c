#include "enemy.h"
#include "game.h"
#include "../util/time.h"
#include <time.h>
#include <stdlib.h>

int old_x = 0;

void enemy_spawn(Enemy *e, int type, int x) {
    if (x == old_x) { // Prevent spawning at equal x
        e->x = rand_between(32, WORLD_WIDTH - 32);
    } else {
        e->x = x;
    }
    old_x = x;
    e->y = -10; // hiding from screen
    e->type = type;
    e->alive = 1;
    e->health = 100;
    e->speed = 3;
    e->width = e->height = 32;
}

void enemy_shoot() {

}

void enemy_move(Enemy *e) {
    e->y += e->speed; // going down
}
