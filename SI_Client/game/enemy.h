#ifndef SI_CLIENT_ENEMY_H
#define SI_CLIENT_ENEMY_H

typedef struct Enemy {
    int x, y;
    int type;
    int health;
    int width, height;
    int alive;
} Enemy;

void enemy_update(Enemy *e, int x, int y, int type, int health);
void enemy_render(Enemy *e, SDL_Rect *bounds);
void enemy_dump(Enemy* e, int x, int y, int type, int health, int alive);

#endif //SI_CLIENT_ENEMY_H
