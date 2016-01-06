#include "enemy.h"
#include "game.h"
#include <time.h>
#include <stdlib.h>

void enemy_spawn(Enemy *e, int type) {
    srand(time(NULL)); // TODO: not use rand, get coords from game
    e->x = rand() % WORLD_WIDTH;
    e->y = -10; // hiding from screen
    e->type = type;
    e->alive = 1;
    e->health = 100;
    e->speed = 3; // speed?
    e->width = e->height = 32;
}

void enemy_shoot() {

}

void enemy_move(Enemy *e) {
    e->y += e->speed; // going down
}
