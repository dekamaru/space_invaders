#include <SDL2/SDL.h>
#include <stdio.h>

#include "engine/engine.h"

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
        E_Update();
        E_Render();
    }

    E_Shutdown();
    return EXIT_SUCCESS;
}