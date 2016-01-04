//
// Created by dekamaru on 02.01.16.
//

#ifndef SI_CLIENT_FONT_H
#define SI_CLIENT_FONT_H

#include <SDL2/SDL_render.h>
SDL_Rect font_render(char* message, int x, int y, int centered, TTF_Font *font, SDL_Color color);

#endif //SI_CLIENT_FONT_H
