#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "engine.h"
#include "assets.h"

int E_Init() {
    // Engine initialization (textures, sounds, etc...)
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0) {
        //log: init failed
        return 0;
    }

    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        //log: create window error (SDL_GetError())
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        // log: create renderer error
        return 0;
    }

    // TODO: load assets!

    Assets* assets_bundle = assets_init();
    assets_load_font(assets_bundle, "assets/font.ttf", 36);
    assets_load_font(assets_bundle, "assets/font.ttf", 24);
    assets_load_font(assets_bundle, "assets/font.ttf", 18);

    // ALL THINGS DONE, GO TO MAIN MENU
    switch_screen(&current_screen, 1, assets_bundle);
    return 1;
}

int E_HandleEvent(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        E_Shutdown();
    } else {
        current_screen.event(event);
    }
}

int E_Update() {
    current_screen.update();
}

int E_Render() {
    SDL_RenderClear(renderer);
    current_screen.draw(renderer);
    SDL_RenderPresent(renderer);
}

int E_Shutdown() {
    // Game exit, cleanup resources, memory..
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    state = SHUTDOWN;
}


