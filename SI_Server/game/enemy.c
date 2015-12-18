#include "enemy.h"
#include "game.h"
#include <time.h>
#include <stdlib.h>

Enemy enemy_spawn(int type) {
    srand(time(NULL));
    Enemy e;
    e.x = rand() % WORLD_WIDTH;
    e.y = -20; // hiding from screen
    e.type = type;
    e.alive = 1;
    e.health = 100;
    e.width = e.height = 32;
    return e;
}

void enemy_destroy(Enemy* e) {
    e->alive = 0;
}
