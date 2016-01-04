//
// Created by dekamaru on 02.01.16.
//

#include <SDL2/SDL_ttf.h>
#include "font.h"

SDL_Rect font_render(char* message, int x, int y, int centered, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer) {
    int w, h;
    SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect dest;
    if (centered == 1) {
        x = 640 / 2 - w / 2;
    }
    dest.x = x;
    dest.y = y;
    dest.h = h;
    dest.w = w;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    return dest;
}