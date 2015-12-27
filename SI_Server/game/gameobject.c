#include "gameobject.h"

void gameobject_move(GameObject* go) {
    if (go->owner == 1) {
        go->y -= go->speed; // from player bullet
    } else {
        go->y += go->speed; // from enemy bullet
    }
}
