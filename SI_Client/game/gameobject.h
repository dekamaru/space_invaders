//
// Created by dekamaru on 08.01.16.
//

#ifndef SI_CLIENT_GAMEOBJECT_H
#define SI_CLIENT_GAMEOBJECT_H

#include <SDL2/SDL_rect.h>

typedef struct GameObject {
    int x, y;
    int type;
    int width, height;
} GameObject;

GameObject* go_dump(int x, int y, int type);
void go_render(GameObject *go, SDL_Rect *bounds);

#endif //SI_CLIENT_GAMEOBJECT_H
