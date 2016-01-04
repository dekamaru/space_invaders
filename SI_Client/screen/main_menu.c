#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#include "main_menu.h"
#include "../util/font.h"
#include "../engine/renderer.h"
#include "../engine/engine.h"

void main_menu_init(E_Screen* s, Assets* a) {
    screen = s;
    assets = a;

    // Menu
    menu_items[0] = "Start game";
    menu_items[1] = "Close";
    menu_pointer = -1;
}

void main_menu_draw(void* renderer) {
    SDL_Renderer *rend = (SDL_Renderer*) renderer;
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    font_render("Space Invaders", 0, 50, 1, assets->fonts[0], white, rend);

    for(int i = 0; i < MENU_ITEMS_COUNT; i++) {
        SDL_Color item_color = (menu_pointer == i) ? red : white;
        if (menu_pointer == -1) item_color = white;
        SDL_Rect menu_border = font_render(menu_items[i], 0, 140 + (i * 50), 1, assets->fonts[2], item_color, rend);
        renderer_set_padding(&menu_border, 20);
        menu_borders[i] = menu_border;
        renderer_draw_rect(&menu_border, renderer, item_color);
    }
}

void main_menu_update() {
}

void main_menu_event(void* event) {
    SDL_Event *e = (SDL_Event*) event;
    switch(e->type) {
        case SDL_MOUSEMOTION:
            menu_pointer = -1;
            for(int i = 0; i < MENU_ITEMS_COUNT; i++) {
                if (
                    e->motion.x >= menu_borders[i].x &&
                    e->motion.x <= menu_borders[i].x + menu_borders[i].w &&
                    e->motion.y >= menu_borders[i].y &&
                    e->motion.y <= menu_borders[i].y + menu_borders[i].h
                ) {
                    menu_pointer = i;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
                main_menu_select();
            break;
        default:
            break;
    }

}

void main_menu_select() {
    switch(menu_pointer) {
        case 0:
            break;
        case 1:
            E_Shutdown(); // close engine
            break;
        default:
            break;
    }
}
