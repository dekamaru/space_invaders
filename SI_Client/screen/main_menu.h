#ifndef SI_CLIENT_MAIN_MENU_H
#define SI_CLIENT_MAIN_MENU_H

#include <SDL2/SDL_ttf.h>
#include "../engine/screen.h"
#include "../engine/assets.h"

typedef struct menu {
    int items_count;
    char* title;
    char* items[10];
    SDL_Rect borders[10];
} menu;

void main_menu_init();
void main_menu_draw();
void main_menu_event(void* event);
void main_menu_update();
void main_menu_select();
void main_render_menu(int menu_part);

int menu_pointer;
int menu_part;

menu m_main;
menu m_retry;
menu menus[2];

#endif //SI_CLIENT_MAIN_MENU_H
