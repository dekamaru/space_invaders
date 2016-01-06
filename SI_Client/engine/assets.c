#include "assets.h"

void assets_load_font(Assets *bundle, char *font_file, int ptsize) {
    bundle->fonts[bundle->font_index] = TTF_OpenFont(font_file, ptsize);
    bundle->font_index++;
}

Assets *assets_init() {
    Assets* bundle = malloc(sizeof(Assets));
    bundle->font_index = 0;
    bundle->fonts = malloc(sizeof(TTF_Font*) * 5); // five fonts
    return bundle;
}
