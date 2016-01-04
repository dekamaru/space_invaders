#ifndef SI_CLIENT_MAIN_MENU_H
#define SI_CLIENT_MAIN_MENU_H

#include <SDL2/SDL_ttf.h>
#include "../engine/screen.h"
#include "../engine/assets.h"

#define MENU_ITEMS_COUNT 2

void main_menu_init(E_Screen *s, Assets *a);
void main_menu_draw(void* renderer);
void main_menu_event(void* event);
void main_menu_update();
void main_menu_select();

E_Screen *screen;
Assets* assets;

// Menu purposes
int menu_pointer;
char *menu_items[MENU_ITEMS_COUNT];
SDL_Rect menu_borders[MENU_ITEMS_COUNT];

#endif //SI_CLIENT_MAIN_MENU_H
