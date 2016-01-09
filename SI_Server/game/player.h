#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#define PLAYER_SPEED 5

typedef struct Player {
    int x, y;
    int health;
    int width, height; // for collision box
    int score;
} Player;

Player player_create(int x, int y);
void player_move(Player *p, int direction);

#endif // GAME_PLAYER_H
