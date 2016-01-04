#include "screen.h"
#include "../screen/main_menu.h"
#include "../screen/game.h"
#include "engine.h"

void switch_screen(int screen_id) {
    switch(screen_id) {
        case 1:
            current_screen.draw = &main_menu_draw;
            current_screen.update = &main_menu_update;
            current_screen.event = &main_menu_event;
            main_menu_init();
            break;
        case 2:
            current_screen.draw = &game_draw;
            current_screen.update = &game_update;
            current_screen.event = &game_event;
            game_init();
            break;
        default:
            break;
    }
}
