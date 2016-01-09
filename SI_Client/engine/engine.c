#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "engine.h"
#include "../game/gameobject.h"

GameObject stars[100];
int stars_counter;

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

    assets_bundle = assets_init();

    /*
     * Fonts
     */
    assets_load_font(assets_bundle, "assets/font.ttf", 36);
    assets_load_font(assets_bundle, "assets/font.ttf", 24);
    assets_load_font(assets_bundle, "assets/font.ttf", 18);
    assets_load_font(assets_bundle, "assets/font.ttf", 12);

    /*
     * Images
     */
    assets_load_image(assets_bundle, "assets/player.png");
    assets_load_image(assets_bundle, "assets/bullet-player.png");
    assets_load_image(assets_bundle, "assets/bullet-enemy.png");
    assets_load_image(assets_bundle, "assets/enemy.png");
    assets_load_image(assets_bundle, "assets/bg.png");

    stars_counter = 0;
    // ALL THINGS DONE, GO TO MAIN MENU
    switch_screen(1);
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
    if (rand() % 5 == 1) {
        if (stars_counter != 100) {
            stars[stars_counter].x = rand() % 640;
            stars[stars_counter].y = -10;
            stars[stars_counter].type = 1 + rand() % 5;
            stars[stars_counter].owner = 3;
            stars_counter++;
        }
    }
    for(int i = 0; i < 100; i++) {
        if (stars[i].y > 480) stars[i].y = -10;
        stars[i].y += stars[i].type;
    }
    current_screen.update();
}

int E_Render() {
    SDL_RenderClear(renderer);

    /**
     * Draw background
     */

    // Image
    SDL_Rect bg_rect;
    bg_rect.x = bg_rect.y = 0;
    bg_rect.w = 640;
    bg_rect.h = 480;
    SDL_RenderCopy(renderer, assets_bundle->images[4], NULL, &bg_rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i = 0; i < 100; i++) {
        SDL_RenderDrawPoint(renderer, stars[i].x, stars[i].y);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    current_screen.draw(renderer);
    SDL_RenderPresent(renderer);
}

int E_Shutdown() {
    // TODO: clear assets
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    state = SHUTDOWN;
}


