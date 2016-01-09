#include "assets.h"
#include "engine.h"

void assets_load_font(Assets *bundle, char *font_file, int ptsize) {
    bundle->fonts[bundle->font_index] = TTF_OpenFont(font_file, ptsize);
    bundle->font_index++;
}

Assets *assets_init() {
    Assets* bundle = malloc(sizeof(Assets));
    bundle->font_index = 0;
    bundle->fonts = malloc(sizeof(TTF_Font*) * 5); // 5 fonts
    bundle->images = malloc(sizeof(SDL_Surface) * 30); // 30 images
    bundle->image_index = 0;
    return bundle;
}

void assets_load_image(Assets *bundle, char *image_path) {
    bundle->images[bundle->image_index] = IMG_LoadTexture(renderer, image_path);
    bundle->image_index++;
}
