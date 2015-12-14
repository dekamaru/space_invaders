#ifndef NETWORK_PACKER_H
#define NETWORK_PACKER_H

#include "../game/player.h"
#include "../game/enemy.h"
#include "../game/gameobject.h"
#include "../game/field.h"

void packer_pack_player(char* buffer, Player* p);
void packer_pack_enemy(char* buffer, Enemy* e);
void packer_pack_gameobject(char* buffer, GameObject* go);
char* packer_pack_field(Field *f);

#endif // NETWORK_PACKER_H
