#include "screen.h"
#include "../screen/main_menu.h"

void switch_screen(E_Screen *s, int screen_id) {
    switch(screen_id) {
        case 1:
            s->draw = &main_menu_draw;
            s->update = &main_menu_update;
            s->event = &main_menu_event;
            break;
        default:
            s->draw = &main_menu_draw;
            s->update = &main_menu_update;
            s->event = &main_menu_event;
            break;
    }
}
