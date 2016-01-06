#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

typedef struct Enemy {
    int x, y;
    int health;
    int width, height; // for collision box
    int speed;
    int type;
    int alive;
} Enemy;

void enemy_spawn(Enemy *e, int type);
void enemy_shoot();
void enemy_move(Enemy *e);

#endif // GAME_ENEMY_H
