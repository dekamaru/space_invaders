#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#ifndef SI_CLIENT_RENDERER_H
#define SI_CLIENT_RENDERER_H

void renderer_set_padding(SDL_Rect *r, int padding);
void renderer_draw_rect(SDL_Rect *r, SDL_Color color);
void renderer_fill_rect(SDL_Rect *r, SDL_Color color);
void renderer_draw_rect_border(SDL_Rect *r, SDL_Color color, SDL_Color border, int border_size);
int renderer_mouse_in_rect(SDL_Rect *r, int x, int y);

#endif //SI_CLIENT_RENDERER_H
