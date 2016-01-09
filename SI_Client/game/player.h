//
// Created by dekamaru on 05.01.16.
//

#ifndef SI_CLIENT_PLAYER_H
#define SI_CLIENT_PLAYER_H

#define SHOOT_COOLDOWN 400 // in ms
uint32_t player_last_shoot;

typedef struct Player {
    int x, y;
    int health;
    int score;
    int width, height;
} Player;

Player* player_create();
void player_update(Player *p, int x, int y, int health, int score);
void player_render(Player *p, int c_id);

#endif //SI_CLIENT_PLAYER_H
