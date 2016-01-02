#ifndef SI_CLIENT_SCREEN_H
#define SI_CLIENT_SCREEN_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

typedef struct E_Screen {
    void (*update)();
    void (*draw)(void*);
    void (*event)(void*);
} E_Screen;

void switch_screen(E_Screen *s, int screen_id);

#endif //SI_CLIENT_SCREEN_H
