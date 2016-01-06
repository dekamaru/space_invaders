#ifndef NETWORK_PACKER_H
#define NETWORK_PACKER_H

#include "../game/player.h"
#include "../game/enemy.h"
#include "../game/gameobject.h"
#include "../game/field.h"

int packer_pack_player(char* buffer, Player* p);
int packer_pack_enemy(char* buffer, Enemy* e);
int packer_pack_gameobject(char* buffer, GameObject* go);
void packer_pack_field(char* buffer, Field *f);

#endif // NETWORK_PACKER_H
