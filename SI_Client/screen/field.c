#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "field.h"
#include "../util/font.h"
#include "../engine/engine.h"
#include "game.h"
#include "../game/gameobject.h"
#include "../engine/renderer.h"

/**
 * FPS variables
 */
#define FPS_INTERVAL 1.0
Uint32 fps_lasttime;
Uint32 fps_current;
Uint32 fps_frames;

Player *players[MAX_PLAYERS];
int players_count, started, player_direction;
Queue* packets_send;
Queue* enemies;
Queue* gameobjects;
SDL_Rect* bounds;

void field_init() {
    // Init global variables
    players_count = 0; started = 1; player_direction = -1;
    fps_lasttime = SDL_GetTicks();
    fps_frames = 0;

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
    font_render("SI alpha v 0.3 - Work in progress", 0, 0, 0, assets_bundle->fonts[2], w);
    char* info = malloc(20);
    sprintf(info, "Lives: %i", players[client_id]->lives);
    font_render(info, 0, 20, 0, assets_bundle->fonts[2], w);
    sprintf(info, "Score: %i", players[client_id]->score);
    font_render(info, 0, 40, 0, assets_bundle->fonts[2], w);

    // TODO: fix stun player if shooting & moving
    for(int i = 0; i < MAX_PLAYERS; i++) player_render(players[i]);
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
    char* buffer = malloc(3);
    Packet *p;
    switch(e->type) {
        case SDL_KEYDOWN:
            switch(e->key.keysym.sym) {
                case SDLK_LEFT:
                    sprintf(buffer, "%i:%i", client_id, 0);
                    p = (Packet*) net_create_packet(4, 3, buffer);
                    queue_push(packets_send, p);
                    break;
                case SDLK_RIGHT:
                    sprintf(buffer, "%i:%i", client_id, 1);
                    p = (Packet*) net_create_packet(4, 3, buffer);
                    queue_push(packets_send, p);
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(e->key.keysym.sym) {
                case SDLK_SPACE:
                    sprintf(buffer, "%i", client_id);
                    Packet *s = (Packet*) net_create_packet(5, 1, buffer);
                    queue_push(packets_send, s);
                    break;
                default:
                    break;
            }
            break;
    }
}

void field_update() {
}

void receiver_thread() {

    while(started) {
        Packet *p = net_receive_packet();
        if (p->packet_id == 3) {
            field_parse_packet(p->data);
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