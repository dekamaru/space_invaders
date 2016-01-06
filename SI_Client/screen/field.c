#include <pthread.h>
#include <stdio.h>
#include "field.h"
#include "../engine/network.h"
#include "../util/font.h"
#include "../engine/engine.h"
#include "game.h"

void field_init() {
    players_count = 0; started = 1; player_direction = -1;
    pthread_t receiver_t, sender_t;
    pthread_create(&receiver_t, NULL, receiver_thread, NULL);
    pthread_create(&sender_t, NULL, sender_thread, NULL);
    packets_send = queue_create();
    for(int i = 0; i < MAX_PLAYERS; i++) players[i] = player_create();
}

void field_draw(void *renderer) {
    SDL_Color w = {255, 255, 255, 255};
    font_render("SI alpha v 0.1 - Work in progress", 0, 0, 0, assets_bundle->fonts[2], w);
    for(int i = 0; i < MAX_PLAYERS; i++) player_render(players[i]);
}

void field_event(void *event) {
    SDL_Event* e = (SDL_Event*) event;
    char* buffer = malloc(3);
    Packet *p;
    switch(e->type) {
        case SDL_KEYDOWN:
            switch(e->key.keysym.sym) {
                case SDLK_LEFT:
                    player_direction = 0;
                    break;
                case SDLK_RIGHT:
                    player_direction = 1;
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(e->key.keysym.sym) {
                case SDLK_LEFT:
                    if (player_direction == 0) player_direction = -1;
                    break;
                case SDLK_RIGHT:
                    if (player_direction == 1) player_direction = -1;
                    break;
                default:
                    break;
            }
            break;
    }
    if (player_direction != -1) {
        sprintf(buffer, "%i:%i", client_id, player_direction);
        p = (Packet*) net_create_packet(4, 3, buffer);
        queue_push(packets_send, p);
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
    }
}

void sender_thread() {
    while(started) {
        while(!queue_empty(packets_send)) {
            Packet *p = queue_pop(packets_send);
            char *buf = (char*) p;
            net_send_packet(buf, sizeof(Packet) + p->data_length);
            free(buf);
        }
    }
}

void field_parse_packet(char* packet) {
    int id, a1, a2, a3, a4, pos;
    while(sscanf(packet, "%i:%i:%i:%i:%i:%n", &id, &a1, &a2, &a3, &a4, &pos) == 5) {
        packet += pos;
        field_resolve_data(id, a1, a2, a3, a4);
    }
}

void field_resolve_data(int id, int a1, int a2, int a3, int a4) {
    switch(id) {
        case 1:
            player_update(players[players_count], a1, a2, a3, a4);
            players_count = (players_count == 1) ? 0 : 1;
            break;
        default:
            break;
    }
}