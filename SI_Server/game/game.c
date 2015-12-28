#include "game.h"

#include <time.h>
#include <stdlib.h>

void game_init(Field* field) {
    field->players[0] = player_create(32, WORLD_HEIGHT - 32);
    field->players[1] = player_create(WORLD_WIDTH - 64, WORLD_HEIGHT - 32);
}

void game_update(Field* field) {
    srand(time(NULL));
    game_update_gameobjects(field);
    game_update_enemies(field);
}

void game_packet_handle(int packet_id, char* packet_data, Field *f) {
    switch(packet_id) {
        case 4:
        {
            // PLAYER_MOVE (id player, direction)
            //int player_id = packet_read_int(&packet_data);
            //int direction = packet_read_int(&packet_data); TODO!!!
            //player_move(&f->players[player_id], direction);
        }
        break;
    }
}

void game_update_gameobjects(Field* field) {
    for(int i = 0; i < MAX_OBJECTS; i++) {
        if (field->objects[i].alive == 1) {
            gameobject_move(&field->objects[i]); // update coords
            if (field->objects[i].y > WORLD_HEIGHT) { // if out of screen
                field->objects[i].alive = 0; // destroy object
            }
            // CHECK COLISSIONS!
        }
    }
}

void game_update_enemies(Field* field) {
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if (field->enemies[i].alive == 1) {
            //enemy_move(&field->enemies[i]); //TODO: release that
            if (rand() % 1000 == ENEMY_SHOOT_CHANCE) {
                //enemy_shoot(); // TODO: release that
            }
            if(field->enemies[i].y > WORLD_HEIGHT) {
                field->enemies[i].alive = 0;
            }
            // TODO: CHECK COLISSION WITH PLAYER

        }
    }

    if (field_enemies_count(field) < MAX_SPAWNED_ENEMIES) {
        if (rand() % 1000 == ENEMY_SPAWN_CHANCE) {
            int write_index = field_enemies_find_space(field);
            field->enemies[write_index] = enemy_spawn(1); // spawn enemy with type 1
        }
    }
}
