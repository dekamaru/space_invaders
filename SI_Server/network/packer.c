#include "packer.h"
/*
        FIELD OBJECT TYPES:
        1 - player (x, y, lives)
        2 - enemy (x, y, health, type, alive)
        3 - gameobject (x, y, type, alive)

        Example: 1:x:y:lives:2:enemy:x:y:type:alive:3:x:y:type:alive
*/
void packer_pack_player(char* buffer, Player* p) {
    packet_write_int(buffer, 1);
    packet_write_int(buffer, p->x);
    packet_write_int(buffer, p->y);
    packet_write_int(buffer, p->lives);
}

void packer_pack_enemy(char* buffer, Enemy* e) {
    packet_write_int(buffer, 2);
    packet_write_int(buffer, e->x);
    packet_write_int(buffer, e->y);
    packet_write_int(buffer, e->type);
    packet_write_int(buffer, e->health);
    packet_write_int(buffer, e->alive);
}

void packer_pack_gameobject(char* buffer, GameObject* go) {
    packet_write_int(buffer, 3);
    packet_write_int(buffer, go->x);
    packet_write_int(buffer, go->y);
    packet_write_int(buffer, go->type);
    packet_write_int(buffer, go->alive);
}

char* packer_pack_field(Field *f) {
    char* buffer = malloc(4096);
    packer_pack_player(buffer, &f->players[0]);
    packer_pack_player(buffer, &f->players[1]);
    for(int i = 0; i < 30; i++) {
        if (f->enemies[i].alive == 1) {
            packer_pack_enemy(buffer, &f->enemies[i]);
        }
    }
    for(int i = 0; i < 1000; i++) {
        if (f->objects[i].alive == 1) {
            packer_pack_gameobject(buffer, &f->objects[i]);
        }
    }
    return buffer;
}
