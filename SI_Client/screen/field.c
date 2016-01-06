#include <pthread.h>
#include <stdio.h>
#include "field.h"
#include "../engine/network.h"
#include "../util/font.h"
#include "../engine/engine.h"
#include "game.h"

void field_init() {
    pthread_t receiver_t, sender_t;
    pthread_create(&receiver_t, NULL, receiver_thread, NULL);
    pthread_create(&sender_t, NULL, sender_thread, NULL);
    players_count = 0;
    started = 1;
    packets_send = queue_create();
}

void field_draw(void *renderer) {
    SDL_Color w = {255, 255, 255, 255};
    font_render("SI alpha v 0.1", 0, 0, 0, assets_bundle->fonts[2], w);
    for(int i = 0; i < MAX_PLAYERS; i++) {
        if (players[i] != NULL) player_render(players[i]);
    }
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
    }
}

void field_update() {

}

void receiver_thread() {
    while(started) {
        Packet *p = net_receive_packet();
        if (p->packet_id == 3) {
            field_parse(p->data);
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

// TODO: split in files & function naming???
void field_parse(char* packet) {
    int id, a1, a2, a3, a4, pos;
    while(sscanf(packet, "%i:%i:%i:%i:%i:%n", &id, &a1, &a2, &a3, &a4, &pos) == 5) {
        packet += pos;
        packet_resolve_data(id, a1, a2, a3, a4);
    }
}

void packet_resolve_data(int id, int a1, int a2, int a3, int a4) {
    switch(id) {
        case 1:
            players[players_count] = player_load(a1, a2, a3, a4);
            players_count = (players_count == 1) ? 0 : 1;
            break;
        default:
            break;
    }
}