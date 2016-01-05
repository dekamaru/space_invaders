#include <pthread.h>
#include <stdio.h>
#include "field.h"
#include "../engine/network.h"
#include "../util/font.h"
#include "../engine/engine.h"

void field_init() {
    pthread_t receiver_t;
    pthread_create(&receiver_t, NULL, receiver_thread, NULL);
    players_count = 0;
}

void field_draw(void *renderer) {
    SDL_Color w = {255, 255, 255, 255};
    font_render("SI alpha v 0.1", 0, 0, 0, assets_bundle->fonts[2], w);
    for(int i = 0; i < MAX_PLAYERS; i++) {
        if (players[i] != NULL) player_render(players[i]);
    }
}

void field_event(void *event) {

}

void field_update() {

}

void receiver_thread() {
    int started = 1;
    while(started) {
        Packet *p = net_receive_packet();
        if (p->packet_id == 3) {
            field_parse(p->data);
        }
    }
}

// TODO: split in files
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