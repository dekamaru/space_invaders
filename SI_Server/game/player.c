#include "player.h"

Player player_create(int x, int y) {
    Player p;
    p.x = x;
    p.y = y;
    p.width = p.height = 32;
    p.health = 100;
    p.score = 0;
    p.is_dead = 0;
    return p;
}

void player_move(Player *p, int direction) {
    if (direction == 0) {
        p->x -= PLAYER_SPEED; // left
    } else {
        p->x += PLAYER_SPEED; // right
    }
}

void player_dead(Player *p) {
    p->is_dead = 1;
    p->health = -1;
}
