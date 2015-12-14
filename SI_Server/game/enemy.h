#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

typedef struct Enemy {
    int x, y;
    int health;
    int type;
    int alive;
} Enemy;

#endif // GAME_ENEMY_H
