//
// Created by dekamaru on 04.01.16.
//

#include "renderer.h"
#include "engine.h"

void renderer_set_padding(SDL_Rect *r, int padding) {
    r->w += padding;
    r->h += padding;
    r->x -= padding / 2;
    r->y -= padding / 2;
}

void renderer_draw_rect(SDL_Rect *r, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}
