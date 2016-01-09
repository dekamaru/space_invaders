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

void renderer_fill_rect(SDL_Rect *r, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void renderer_draw_rect_border(SDL_Rect *r, SDL_Color color, SDL_Color border, int border_size) {
    renderer_set_padding(r, border_size);
    renderer_fill_rect(r, border);
    r->x += border_size;
    r->y += border_size;
    r->w -= border_size * 2;
    r->h -= border_size * 2;
    renderer_fill_rect(r, color);
}

int renderer_mouse_in_rect(SDL_Rect *r, int x, int y) {
    return x >= r->x && x <= r->x + r->w && y >= r->y && y <= r->y + r->h;
}
