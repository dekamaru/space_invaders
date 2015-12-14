#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

typedef struct GameObject {
    int x, y;
    int alive;
    int type; // bullet - 1, etc...
} GameObject;

#endif // GAME_OBJECT_H
