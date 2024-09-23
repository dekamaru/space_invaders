//
// Created by dekamaru on 08.01.16.
//

#ifndef SI_CLIENT_GAMEOBJECT_H
#define SI_CLIENT_GAMEOBJECT_H

#include <SDL_rect.h>

typedef struct GameObject {
    int x, y;
    int type;
    int width, height;
    int owner;
    int alive;
} GameObject;

void go_dump(GameObject *go, int x, int y, int type, int owner, int alive);
void go_render(GameObject *go, SDL_Rect *bounds);

#endif //SI_CLIENT_GAMEOBJECT_H
