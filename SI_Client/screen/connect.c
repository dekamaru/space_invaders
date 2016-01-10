//
// Created by dekamaru on 10.01.16.
//

#include "connect.h"
#include "../util/font.h"
#include "../engine/engine.h"
#include "../engine/renderer.h"
#include "../engine/network.h"
#include "main_menu.h"

SDL_Rect connect_bounds[4];
char *inputs[2];
int menu_pointer = -1;
int current_input = -1;
int input_pointer = 0;

void connect_init() {
    connect_bounds[0] = (SDL_Rect) {640 / 2 - 100, 120, 200, 40}; // server_input
    connect_bounds[1] = (SDL_Rect) {640 / 2 - 100, 220, 200, 40}; // port_input
    connect_bounds[2] = (SDL_Rect) {640 / 2 - 100, 290, 200, 40}; // connect_button
    connect_bounds[3] = (SDL_Rect) {640 / 2 - 100, 340, 200, 40}; // back_button
    for(int i = 0; i < 2; i++) {
        inputs[i] = calloc(50, sizeof(char));
    }
    strcpy(inputs[0], DEFAULT_IP);
    strcpy(inputs[1], DEFAULT_PORT);
}

void connect_draw(void *renderer) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    font_render("Connect to server:", 0, 20, 1, assets_bundle->fonts[0], white);
    font_render("Server IP:", 0, 90, 1, assets_bundle->fonts[2], white);
    font_render("Port:", 0, 190, 1, assets_bundle->fonts[2], white);
    font_render("Connect", 0, 300, 1, assets_bundle->fonts[2], white);
    font_render("Back", 0, 350, 1, assets_bundle->fonts[2], white);
    font_render(inputs[0], 640 / 2 - 90, 130, 0, assets_bundle->fonts[2], white);
    font_render(inputs[1], 640 / 2 - 90, 230, 0, assets_bundle->fonts[2], white);

    for(int i = 0; i < 4; i++) {
        SDL_Color current = (menu_pointer == i || current_input == i) ? red : white;
        renderer_draw_rect(&connect_bounds[i], current);
    }

}

void connect_event(void *event) {
    SDL_Event *e = (SDL_Event*) event;
    switch(e->type) {
        case SDL_MOUSEMOTION:
            menu_pointer = -1;
            for(int i = 0; i < 4; i++) {
                if (renderer_mouse_in_rect(&connect_bounds[i], e->motion.x, e->motion.y)) {
                    menu_pointer = i;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            current_input = -1;
            if (menu_pointer != -1) {
                switch(menu_pointer) {
                    case 0:
                        current_input = 0;
                        input_pointer = strlen(inputs[current_input]);
                        break;
                    case 1:
                        current_input = 1;
                        input_pointer = strlen(inputs[current_input]);
                        break;
                    case 2:
                        if (net_client_connect(inputs[0], atoi(inputs[1])) == 1) {
                            switch_screen(2);
                        } else {
                            switch_screen(1);
                            menu_part = 1; // Retry menu
                        }
                        break;
                    case 3:
                        switch_screen(1);
                        break;
                }
            }
            break;
        case SDL_KEYDOWN:
                if (current_input != -1) {
                    if (e->key.keysym.sym == SDLK_BACKSPACE && input_pointer != 0) {
                        inputs[current_input][input_pointer - 1] = 0;
                        input_pointer--;
                    } else {
                        if (input_pointer < 18 && e->key.keysym.sym != SDLK_BACKSPACE) {
                            inputs[current_input][input_pointer] = e->key.keysym.sym;
                            input_pointer++;
                        }
                    }
                }
            break;
        default:
            break;
    }
}

void connect_update() {

}
