#include <pthread.h>
#include <stdio.h>
#include "field.h"
#include "../util/font.h"
#include "../engine/engine.h"
#include "game.h"
#include "../game/gameobject.h"
#include "../engine/network.h"

#define FPS_INTERVAL 1.0
Uint32 fps_lasttime, fps_current, fps_frames;
int players_count, started, last_health, blood_screen;
int keyboard[3];
SDL_Rect* bounds;
Field* field;

void field_init() {
    // Init global variables
    players_count = 0; started = 1; last_health = 100; fps_frames = 0;
    blood_screen = 0;
    fps_lasttime = SDL_GetTicks();
    player_last_shoot = SDL_GetTicks();

    field = calloc(1, sizeof(Field));

    bounds = malloc(sizeof(SDL_Rect));

    // Allocate memory for game entities
    for(int i = 0; i < MAX_PLAYERS; i++) {
        player_create(&field->players[i]);
    }

    // Init receive thread
    pthread_t receiver_t;
    pthread_create(&receiver_t, NULL, receiver_thread, NULL);
}

void field_draw(void *renderer) {
    SDL_Color w = {255, 255, 255, 255};
    font_render("SI alpha v 0.4 - Work in progress", 0, 0, 0, assets_bundle->fonts[2], w);
    char* info = malloc(20);
    if (!field->players[client_id].is_dead) {
        sprintf(info, "Health: %i", field->players[client_id].health);
    } else {
        sprintf(info, "You are dead!");
    }
    font_render(info, 0, 20, 0, assets_bundle->fonts[2], w);
    sprintf(info, "Score: %i", field->players[client_id].score);
    font_render(info, 0, 40, 0, assets_bundle->fonts[2], w);

    for(int i = 0; i < MAX_PLAYERS; i++) {
        if (!field->players[i].is_dead) {
            player_render(&field->players[i], i);
        }
    }

    for(int i = 0; i < MAX_ENEMIES; i++) {
        if (field->enemies[i].alive) {
            enemy_render(&field->enemies[i], bounds);
        }
    }

    for(int i = 0; i < MAX_OBJECTS; i++) {
        if (field->objects[i].alive) {
            go_render(&field->objects[i], bounds);
        }
    }

    if (blood_screen) {
        bounds->x = bounds->y = 0;
        bounds->w = 640; bounds->h = 480;
        SDL_RenderCopy(renderer, assets_bundle->images[5], NULL, bounds);
        blood_screen = 0;
    }

    /**
     * Calculating drawing fps
     */
    fps_frames++;
    if (fps_lasttime < SDL_GetTicks() - FPS_INTERVAL * 1000)
    {
        fps_lasttime = SDL_GetTicks();
        fps_current = fps_frames;
        fps_frames = 0;

    }
    sprintf(info, "FPS: %i", fps_current);
    font_render(info, 0, 60, 0, assets_bundle->fonts[2], w);

    free(info);
}

void field_event(void *event) {
    SDL_Event* e = (SDL_Event*) event;
    switch(e->type) {
        case SDL_KEYDOWN:
            switch(e->key.keysym.sym) {
                case SDLK_LEFT:
                    keyboard[0] = 1;
                    break;
                case SDLK_RIGHT:
                    keyboard[1] = 1;
                    break;
                case SDLK_SPACE:
                    keyboard[2] = 1;
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(e->key.keysym.sym) {
                case SDLK_LEFT:
                    keyboard[0] = 0;
                    break;
                case SDLK_RIGHT:
                    keyboard[1] = 0;
                    break;
                case SDLK_SPACE:
                    keyboard[2] = 0;
                    break;
                default:
                    break;
            }
            break;
    }
}

void field_update() {
    score = field->players[client_id].score;
    for(int i = 0; i < MAX_PLAYERS; i++) {
        if (field->players[i].health == -1) {
            field->players[i].is_dead = 1;
        }
    }
    if (field->players[client_id].health > last_health) last_health = field->players[client_id].health; // restore, if pickup'd healthpack
    if (last_health > field->players[client_id].health && !field->players[client_id].is_dead) {
        last_health = field->players[client_id].health;
        blood_screen = 1;
    }
    if (!field->players[client_id].is_dead) {
        if (keyboard[0]) {
            char* buffer = malloc(3);
            sprintf(buffer, "%i:%i", client_id, 0);
            Packet *p = (Packet*) net_create_packet(4, 3, buffer);
            net_send_packet((char*) p, sizeof(Packet) + p->data_length);
            free(p);
        }

        if (keyboard[1]) {
            char* buffer = malloc(3);
            sprintf(buffer, "%i:%i", client_id, 1);
            Packet *p = (Packet*) net_create_packet(4, 3, buffer);
            net_send_packet((char*) p, sizeof(Packet) + p->data_length);
            free(p);
        }

        if (keyboard[2]) {
            char* buffer = malloc(3);
            uint32_t current_tick = SDL_GetTicks();
            if (current_tick - player_last_shoot >= SHOOT_COOLDOWN) {
                sprintf(buffer, "%i", client_id);

                Packet *p = (Packet*) net_create_packet(5, 1, buffer);
                net_send_packet((char*) p, sizeof(Packet) + p->data_length);
                free(p);

                player_last_shoot = current_tick;
            }
        }
    }
}

void* receiver_thread() {

    while(started) {
        Packet *p = net_receive_packet();
        if (p == NULL) {
            // server closed
            started = 0;
            switch_screen(5);
            return NULL;
        }
        switch(p->packet_id) {
            case 3:
                field_parse_packet(p->data);
                break;
            case 8:
                started = 0;
                switch_screen(5); // game over screen
                break;
            default:
                break;
        }
        free(p);
    }

    return NULL;
}

void field_parse_packet(char* data) {
    int reset = 0;
    int id, a1, a2, a3, a4, a5, pos;
    int e_idx = 0; int o_idx = 0;
    while(sscanf(data, "%i:%i:%i:%i:%i:%i:%n", &id, &a1, &a2, &a3, &a4, &a5, &pos) == 6) {
        data += pos;
        reset += pos;

        switch(id) {
            case 1:
                // Player field data
                player_update(&field->players[players_count], a1, a2, a3, a4, a5);
                players_count = (players_count == 1) ? 0 : 1;
            break;
            case 2:
                enemy_dump(&field->enemies[e_idx++], a1, a2, a3, a4, a5);
            break;
            case 3:
                go_dump(&field->objects[o_idx++], a1, a2, a3, a4, a5);
            break;
            default:
                break;
        }
    }

    data -= reset;
}