#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#define PLAYER_SPEED 1

typedef struct Player {
    int x, y;
    int lives;
    int width, height; // for collision box
    int score;
} Player;

Player player_create(int x, int y);
void player_move(Player *p, int direction);
void player_shoot();

#endif // GAME_PLAYER_H
