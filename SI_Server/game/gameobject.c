#include "gameobject.h"
#include "enemy.h"

void gameobject_move(GameObject* go) {
    if (go->owner == 1) {
        go->y -= go->speed; // from player bullet
    } else {
        go->y += go->speed; // from enemy bullet
    }
}

void gameobject_spawn(GameObject *go, void* p, int owner, int type) {
    switch(type) {
        case 1:
            // bullet
            go->width = go->height = 16;
            break;
        default:
            go->width = go->height = 32;
            break;
    }
    switch(owner) {
        case 1: {
            Player *o = (Player *) p;
            go->x = o->x + 8;
            go->y = o->y;
        }
            break;
        case 2: {
            Enemy *o = (Enemy * ) p;
            go->x = o->x + 8;
            go->y = o->y;
            break;
        }
    }
    go->author = p;
    go->type = type;
    go->owner = owner;
    go->alive = 1;
    go->speed = 6;
}
