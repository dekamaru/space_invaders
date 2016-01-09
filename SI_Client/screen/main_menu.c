#include <SDL2/SDL_events.h>

#include "main_menu.h"
#include "../util/font.h"
#include "../engine/renderer.h"
#include "../engine/engine.h"
#include "../engine/network.h"

void main_menu_init() {
    m_main.title = "Main menu";
    m_main.items[0] = "Start game";
    m_main.items[1] = "Exit";
    m_main.items_count = 2;

    m_retry.title = "Connection failed!";
    m_retry.items[0] = "Retry";
    m_retry.items[1] = "Back";
    m_retry.items_count = 2;

    menus[0] = m_main;
    menus[1] = m_retry;

    menu_pointer = -1;
    menu_part = 0;
}

void main_menu_draw() {
    SDL_Color white = {255, 255, 255, 255};
    font_render("Space Invaders", 0, 50, 1, assets_bundle->fonts[0], white);
    main_render_menu(menu_part);
}

void main_render_menu(int menu_part) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    for(int i = 0; i < menus[menu_part].items_count; i++) {
        SDL_Color item_color = (menu_pointer == i) ? red : white;
        if (menu_pointer == -1) item_color = white;
        font_render(menus[menu_part].title, 0, 110, 1, assets_bundle->fonts[1], white);
        SDL_Rect menu_border = font_render(menus[menu_part].items[i], 0, 160 + (i * 50), 1, assets_bundle->fonts[2], item_color);
        renderer_set_padding(&menu_border, 20);
        menus[menu_part].borders[i] = menu_border;
        renderer_draw_rect(&menu_border, item_color);
    }
}

void main_menu_event(void* event) {
    SDL_Event *e = (SDL_Event*) event;
    switch(e->type) {
        case SDL_MOUSEMOTION:
            menu_pointer = -1;
            for(int i = 0; i < menus[menu_part].items_count; i++) {
                if (renderer_mouse_in_rect(&menus[menu_part].borders[i], e->motion.x, e->motion.y)) {
                    menu_pointer = i;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
                if (menu_pointer != -1) {
                    main_menu_select();
                }
            break;
        default:
            break;
    }

}

void main_menu_select() {
    switch(menu_part) {
        case 0:
            if (menu_pointer == 0) {
                switch_screen(4);
            } else {
                E_Shutdown();
            }
            break;
        case 1:
            if (menu_pointer == 0) {
                switch_screen(4);
            } else {
                menu_part = 0;
            }
            break;
    }
}

void main_menu_update() {}