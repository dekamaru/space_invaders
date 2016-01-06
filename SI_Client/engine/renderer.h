#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#ifndef SI_CLIENT_RENDERER_H
#define SI_CLIENT_RENDERER_H

void renderer_set_padding(SDL_Rect *r, int padding);
void renderer_draw_rect(SDL_Rect *r, SDL_Color color);

#endif //SI_CLIENT_RENDERER_H
