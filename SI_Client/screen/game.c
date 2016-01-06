#include <sys/socket.h>
#include <pthread.h>
#include "game.h"
#include "../engine/network.h"
#include "../util/font.h"
#include "../engine/engine.h"

void game_init() {
    Packet *handshake = net_receive_packet();
    sscanf(handshake->data, "%i", &client_id);
    pthread_t wait_t;
    pthread_create(&wait_t, NULL, (void*) game_wait_start, NULL);
}

void game_draw(void *renderer) {
    SDL_Color white = {255, 255, 255, 255};
    font_render("Connected.", 0, 20, 1, assets_bundle->fonts[0], white);
    font_render("Waiting for player...", 0, 80, 1, assets_bundle->fonts[0], white);
}

void game_wait_start() {
    int started = 0;
    while(!started) {
        Packet *p = net_receive_packet();
        if (p->packet_id == 2) {
            free(p);
            switch_screen(3);
            started = 1;
        }
    }
}

void game_update() {}
void game_event(void *event) {}