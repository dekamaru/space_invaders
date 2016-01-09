#include <SDL2/SDL.h>
#include <stdio.h>

#include "engine/engine.h"

#define ENGINE_FPS 30
int fps_timer;

int main(int argc, char* args[])
{
    state = RUNNING;

    if (E_Init() == 0) {
        // Logger: init false
        return EXIT_FAILURE;
    }

    while(state != SHUTDOWN) {
        while(SDL_PollEvent(&event)) {
            E_HandleEvent(&event);
        }
        fps_timer = SDL_GetTicks();
        E_Update();
        fps_timer = SDL_GetTicks() - fps_timer;
        if(fps_timer < 1000 / ENGINE_FPS) {
            SDL_Delay((1000 / ENGINE_FPS) - fps_timer);
        }
        E_Render();
    }

    E_Shutdown();
    return EXIT_SUCCESS;
}