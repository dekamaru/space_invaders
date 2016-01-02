#include "enemy.h"
#include "game.h"
#include <time.h>
#include <stdlib.h>

Enemy enemy_spawn(int type) {
    srand(time(NULL)); // TODO: not use rand, get coords from game
    Enemy e;
    e.x = rand() % WORLD_WIDTH;
    e.y = -20; // hiding from screen
    e.type = type;
    e.alive = 1;
    e.health = 100;
    e.speed = 1; // speed?
    e.width = e.height = 32;
    return e;
}

void enemy_shoot() {

}

void enemy_move(Enemy *e) {
    e->y += e->speed; // going down
}
