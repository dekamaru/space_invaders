#include <stdio.h>
#include <stdlib.h>
#include "packer.h"


int packer_pack_player(char* buffer, Player* p) {
    return sprintf(buffer, "%i:%i:%i:%i:%i:", 1, p->x, p->y, p->lives, p->score);
}

int packer_pack_enemy(char* buffer, Enemy* e) {
    return sprintf(buffer, "%i:%i:%i:%i:%i:", 2, e->x, e->y, e->type, e->health);
}

int packer_pack_gameobject(char* buffer, GameObject* go) {
    return sprintf(buffer, "%i:%i:%i:%i:%i:", 3, go->x, go->y, go->type, go->owner);
}

void packer_pack_field(char* buffer, Field *f) {
    int size = 0, offset = 0;
    for(int i = 0; i < MAX_PLAYERS; i++) {
        offset = packer_pack_player(buffer, &f->players[i]);
        buffer += offset;
        size += offset;
    }
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if (f->enemies[i].alive == 1) {
            offset = packer_pack_enemy(buffer, &f->enemies[i]);
            buffer += offset;
            size += offset;
        }
    }
    for(int i = 0; i < MAX_OBJECTS; i++) {
        if (f->objects[i].alive == 1) {
            offset = packer_pack_gameobject(buffer, &f->objects[i]);
            buffer += offset;
            size += offset;
        }
    }
    buffer -= size;
}
