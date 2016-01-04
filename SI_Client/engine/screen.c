#include "screen.h"
#include "../screen/main_menu.h"

void switch_screen(E_Screen *s, int screen_id, Assets* a) {
    switch(screen_id) {
        case 1:
            s->draw = &main_menu_draw;
            s->update = &main_menu_update;
            s->event = &main_menu_event;
            main_menu_init(s, a);
            break;
        default:
            s->draw = &main_menu_draw;
            s->update = &main_menu_update;
            s->event = &main_menu_event;
            main_menu_init(s, a);
            break;
    }
}
