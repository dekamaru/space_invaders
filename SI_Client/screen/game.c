//
// Created by dekamaru on 04.01.16.
//

#include <sys/socket.h>
#include "game.h"
#include "../engine/network.h"
#include "../util/font.h"
#include "../engine/engine.h"

void game_init() {
    Packet *handshake = net_receive_packet();
    sscanf(handshake->data, "%i", &client_id);
}

void game_draw(void *renderer) {
    SDL_Color white = {255, 255, 255, 255};
    font_render("Waiting for players...", 0, 20, 1, assets_bundle->fonts[0], white);
    char *client_message = malloc(20);
    sprintf(client_message, "Your client ID: %i", client_id);
    font_render(client_message, 0, 80, 1, assets_bundle->fonts[0], white);
    free(client_message);
}

void game_event(void *event) {

}

void game_update() {

}
