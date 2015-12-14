#include "game.h"

void game_init(Field* field) {
    /* Spawn players */
    int player_spawn_point = 10; // spawn point for x axis
    for(int i = 0; i < 2; i++) {
        field->players[i] = player_create(player_spawn_point, 400);
        player_spawn_point += 400; // margin between players
    }
}

void game_packet_handle(int packet_id, char* packet_data, Field *f) {
    switch(packet_id) {
        case 4:
        {
            // PLAYER_MOVE (id player, direction)
            int player_id = packet_read_int(&packet_data);
            int direction = packet_read_int(&packet_data);
            player_move(&f->players[player_id], direction);
        }
        break;
    }
}
