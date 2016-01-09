//
// Created by dekamaru on 09.01.16.
//

#ifndef SI_SERVER_RECTANGLE_H
#define SI_SERVER_RECTANGLE_H

#include "enemy.h"
#include "player.h"
#include "gameobject.h"

typedef struct Rectangle {
    int x, y, w, h;
} Rectangle;

Rectangle enemy_rectangle(Enemy *e);
Rectangle player_rectangle(Player *e);
Rectangle gameobject_rectangle(GameObject *e);
int rectangle_collide(Rectangle *r1, Rectangle *r2);

#endif //SI_SERVER_RECTANGLE_H
