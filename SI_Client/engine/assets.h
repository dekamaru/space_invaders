//
// Created by dekamaru on 04.01.16.
//

#ifndef SI_CLIENT_ASSETS_H
#define SI_CLIENT_ASSETS_H

#include <SDL2/SDL_ttf.h>

typedef struct Assets {
    TTF_Font **fonts;
    int font_index;
} Assets;

Assets* assets_init();
void assets_load_font(Assets* bundle, char* font_file, int ptsize);

#endif //SI_CLIENT_ASSETS_H
