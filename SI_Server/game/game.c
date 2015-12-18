#include "game.h"

void game_init(Field* field) {
    /* Spawn players */
    field->players[0] = player_create(32, WORLD_HEIGHT - 32);
    field->players[1] = player_create(WORLD_WIDTH - 64, WORLD_HEIGHT - 32);
}

void game_update(Field* field) {
    // update enemies, create enemies, shoot enemies
    // clear dead enemies (setting new x,y, type and set alive = true)
    /*
        1. GAMEOBJECTS:
            1. Update gameobjects coordinates
            2. Check gameobject collisions
            3. Check reach bound of world

        2. ENEMIES:
            1. Update enemies coordinates
            2. Check, if enemy reached bound of world, then destroy him
            3. Check enemy collision with player, if collides - set player lives - 1.
            4. Checking chance of shooting enemy

    */
    if (field_enemies_count(f) < MAX_SPAWNED_ENEMIES) {
        //spawn chance, this function calls 60 times on second. Enemy must spawn 1 time on 5 seconds (ex)
        //if (field_enemies_find_space())
    }
    /*
        int MAX_ENEMIES = 10; may be defined?
        field_find_enemy_space -- return index of enemies[] array

    */

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
