//
// Created by dekamaru on 11.01.16.
//

#include "gameover.h"
#include "../engine/engine.h"
#include "../util/font.h"
#include "field.h"

void gameover_init() {

}

void gameover_draw(void *renderer) {
    SDL_Color w = {255, 255, 255, 255};
    font_render("Game over", 0, 10, 1, assets_bundle->fonts[0], w);
    char *buf = malloc(20);
    sprintf(buf, "Your score: %i", score);
    font_render(buf, 0, 80, 1, assets_bundle->fonts[1], w);
    font_render("Press any key to exit...", 0, 120, 1, assets_bundle->fonts[2], w);
}

void gameover_event(void *event) {
    SDL_Event *e = (SDL_Event*) event;
    switch(e->type) {
        case SDL_KEYDOWN:
            E_Shutdown();
            break;
    }
}

void gameover_update() {

}
