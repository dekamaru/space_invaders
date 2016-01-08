//
// Created by dekamaru on 08.01.16.
//

#include <stdlib.h>
#include <SDL2/SDL_render.h>
#include "gameobject.h"
#include "../engine/engine.h"

GameObject *go_dump(int x, int y, int type) {
    GameObject *go = malloc(sizeof(GameObject));
    switch(type) {
        case 1:
            //bullet
            go->width = go->height = 16;
            break;
        default:
            go->width = go->height = 32;
            break;
    }
    go->type = type;
    go->x = x;
    go->y = y;
    return go;
}

void go_render(GameObject *go, SDL_Rect *bounds) {
    bounds->x = go->x;
    bounds->y = go->y;
    bounds->w = go->width;
    bounds->h = go->height;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, bounds);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
