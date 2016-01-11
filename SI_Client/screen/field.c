#include <pthread.h>
#include <stdio.h>
#include "field.h"
#include "../util/font.h"
#include "../engine/engine.h"
#include "game.h"
#include "../game/gameobject.h"

#define FPS_INTERVAL 1.0
Uint32 fps_lasttime, fps_current, fps_frames;
int players_count, started, last_health, blood_screen;
int keyboard[3];
Queue *packets_send, *enemies, *gameobjects;
SDL_Rect* bounds;
Player *players[MAX_PLAYERS];

void field_init() {
    // Init global variables
    players_count = 0; started = 1; last_health = 100; fps_frames = 0;
    blood_screen = 0;
    fps_lasttime = SDL_GetTicks();
    player_last_shoot = SDL_GetTicks();

    bounds = malloc(sizeof(SDL_Rect));

    // Creating send packets queue
    packets_send = queue_create();
    gameobjects = queue_create();
    enemies = queue_create();

    // Allocate memory for game entities
    for(int i = 0; i < MAX_PLAYERS; i++) players[i] = player_create();

    // Init send & receive threads
    pthread_t receiver_t, sender_t;
    pthread_create(&receiver_t, NULL, receiver_thread, NULL);
    pthread_create(&sender_t, NULL, sender_thread, NULL);
}

void field_draw(void *renderer) {
    SDL_Color w = {255, 255, 255, 255};
    font_render("SI alpha v 0.4 - Work in progress", 0, 0, 0, assets_bundle->fonts[2], w);
    char* info = malloc(20);
    if (!players[client_id]->is_dead) {
        sprintf(info, "Health: %i", players[client_id]->health);
    } else {
        sprintf(info, "You are dead!");
    }
    font_render(info, 0, 20, 0, assets_bundle->fonts[2], w);
    sprintf(info, "Score: %i", players[client_id]->score);
    font_render(info, 0, 40, 0, assets_bundle->fonts[2], w);

    for(int i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i]->is_dead) {
            player_render(players[i], i);
        }
    }
    while (!queue_empty(enemies)) {
        Enemy *e = queue_pop(enemies);
        enemy_render(e, bounds);
        free(e);
    }
    while (!queue_empty(gameobjects)) {
        GameObject *go = queue_pop(gameobjects);
        go_render(go, bounds);
        free(go);
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
    score = players[client_id]->score;
    for(int i = 0; i < MAX_PLAYERS; i++) {
        if (players[i]->health == -1) {
            players[i]->is_dead = 1;
        }
    }
    if (last_health > players[client_id]->health && !players[client_id]->is_dead) {
        last_health = players[client_id]->health;
        blood_screen = 1;
    }
    if (!players[client_id]->is_dead) {
        char* buffer = malloc(3);
        Packet *p;
        if (keyboard[0]) {
            sprintf(buffer, "%i:%i", client_id, 0);
            p = (Packet*) net_create_packet(4, 3, buffer);
            queue_push(packets_send, p);
        }
        if (keyboard[1]) {
            sprintf(buffer, "%i:%i", client_id, 1);
            p = (Packet*) net_create_packet(4, 3, buffer);
            queue_push(packets_send, p);
        }
        if (keyboard[2]) {
            uint32_t current_tick = SDL_GetTicks();
            if (current_tick - player_last_shoot >= SHOOT_COOLDOWN) {
                sprintf(buffer, "%i", client_id);
                Packet *s = (Packet*) net_create_packet(5, 1, buffer);
                queue_push(packets_send, s);
                player_last_shoot = current_tick;
            }
        }
    }
}

void receiver_thread() {

    while(started) {
        Packet *p = net_receive_packet();
        if (p == NULL) {
            // server closed
            started = 0;
            switch_screen(5);
            return;
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
}

void sender_thread() {
    while(started) {
        if(!queue_empty(packets_send)) {
            Packet *p = queue_pop(packets_send);
            char *buf = (char*) p;
            net_send_packet(buf, sizeof(Packet) + p->data_length);
            free(buf);
        }
    }
}

void field_parse_packet(char* data) {
    int reset = 0;
    int id, a1, a2, a3, a4, pos;
    while(sscanf(data, "%i:%i:%i:%i:%i:%n", &id, &a1, &a2, &a3, &a4, &pos) == 5) {
        data += pos;
        reset += pos;
        field_resolve_data(id, a1, a2, a3, a4);
    }
    data -= reset;
}

void field_resolve_data(int id, int a1, int a2, int a3, int a4) {
    switch(id) {
        case 1:
            // Player field data
            player_update(players[players_count], a1, a2, a3, a4);
            players_count = (players_count == 1) ? 0 : 1;
            break;
        case 2:
            // Enemy field data
            queue_push(enemies, enemy_dump(a1, a2, a3, a4));
            break;
        case 3:
            // Gameobject field data
            queue_push(gameobjects, go_dump(a1, a2, a3, a4));
            break;
        default:
            break;
    }
}