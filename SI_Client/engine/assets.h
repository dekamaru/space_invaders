#ifndef SI_CLIENT_ASSETS_H
#define SI_CLIENT_ASSETS_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct Assets {
    TTF_Font **fonts;
    SDL_Texture **images;
    int font_index, image_index;
} Assets;

Assets* assets_init();
void assets_load_font(Assets* bundle, char* font_file, int ptsize);
void assets_load_image(Assets* bundle, char* image_path);

#endif //SI_CLIENT_ASSETS_H
