#include "gameobject.h"

void gameobject_move(GameObject* go) {
    if (go->owner == 1) {
        go->y -= go->speed; // from player bullet
    } else {
        go->y += go->speed; // from enemy bullet
    }
}

void gameobject_spawn(GameObject *go, Player* p, int owner, int type) {
    switch(type) {
        case 1:
            // bullet
            go->width = go->height = 16;
            break;
        default:
            go->width = go->height = 32;
            break;
    }
    go->type = type;
    go->owner = owner;
    go->alive = 1;
    go->x = p->x + 8; // center at object
    go->y = p->y;
    go->speed = 6;
}
