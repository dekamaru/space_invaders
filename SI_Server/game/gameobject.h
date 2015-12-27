#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

typedef struct GameObject {
    int x, y;
    int width, height;
    int alive;
    int type; // bullet - 1, etc...
    int owner; // 1 - player, 2 - enemy, 3 - etc...
    int speed;
} GameObject;

void gameobject_move(GameObject* go);

#endif // GAME_OBJECT_H
