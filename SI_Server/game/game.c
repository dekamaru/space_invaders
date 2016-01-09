#include "game.h"
#include "../util/time.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void game_init(Field* field) {
    field->players[0] = player_create(32, WORLD_HEIGHT - 32);
    field->players[1] = player_create(WORLD_WIDTH - 64, WORLD_HEIGHT - 32);
}

void game_update(Field* field) {
    game_update_gameobjects(field);
    game_update_enemies(field);
}

void game_packet_handle(int packet_id, char* packet_data, Field *f) {
    int player_id;
    switch(packet_id) {
        case 4:
        {
            // PLAYER_MOVE (id player, direction)
            int direction;
            sscanf(packet_data, "%i:%i", &player_id, &direction);
            player_move(&f->players[player_id], direction);
        }
        break;
        case 5: {
            sscanf(packet_data, "%i", &player_id);
            int index = field_gameobjects_find_space(f);
            if (index != -1) {
                gameobject_spawn(&f->objects[index], &f->players[player_id], 1, 1); // spawn bullet
            }

        }
        break;
    }
}

void game_update_gameobjects(Field* field) {
    for(int i = 0; i < MAX_OBJECTS; i++) {
        if (field->objects[i].alive == 1) {
            gameobject_move(&field->objects[i]); // update coords
            if (field->objects[i].y > WORLD_HEIGHT || field->objects[i].y < 0) { // if out of screen
                field->objects[i].alive = 0; // destroy object
            }
            // TODO: CHECK COLISSIONS!
        }
    }
}

void game_update_enemies(Field* field) {
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if (field->enemies[i].alive == 1) {
            enemy_move(&field->enemies[i]);
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
        if (rand() % 50 == ENEMY_SPAWN_CHANCE) {
            int write_index = field_enemies_find_space(field);
            if (write_index != -1) {
                int x = rand_between(32, WORLD_WIDTH - 32);
                enemy_spawn(&field->enemies[write_index], 1, x);
            }
        }
    }
}
