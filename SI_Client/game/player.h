//
// Created by dekamaru on 05.01.16.
//

#ifndef SI_CLIENT_PLAYER_H
#define SI_CLIENT_PLAYER_H

typedef struct Player {
    int x, y;
    int lives;
    int score;
    int width, height;
} Player;

Player* player_load(int x, int y, int lives, int score);
void player_render(Player* p);

#endif //SI_CLIENT_PLAYER_H
