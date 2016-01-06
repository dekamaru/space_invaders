#ifndef SI_CLIENT_ENEMY_H
#define SI_CLIENT_ENEMY_H

typedef struct Enemy {
    int x, y;
    int type;
    int health;
    int width, height;
} Enemy;

Enemy* enemy_create(int x, int y, int type, int health);
void enemy_render(Enemy *e);

#endif //SI_CLIENT_ENEMY_H
