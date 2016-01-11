#include "screen.h"
#include "../screen/main_menu.h"
#include "../screen/game.h"
#include "engine.h"
#include "../screen/field.h"
#include "../screen/connect.h"
#include "../screen/gameover.h"

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
        case 3:
            current_screen.draw = &field_draw;
            current_screen.update = &field_update;
            current_screen.event = &field_event;
            field_init();
            break;
        case 4:
            current_screen.draw = &connect_draw;
            current_screen.update = &connect_update;
            current_screen.event = &connect_event;
            connect_init();
            break;
        case 5:
            current_screen.draw = &gameover_draw;
            current_screen.update = &gameover_update;
            current_screen.event = &gameover_event;
            gameover_init();
            break;
        default:
            break;
    }
}
