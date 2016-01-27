#include "game.h"
#include "../util/time.h"
#include "rectangle.h"
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
            const int index = field_gameobjects_find_space(f);
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
            if (field->objects[i].y > WORLD_HEIGHT || field->objects[i].y < -10) { // if out of screen
                field->objects[i].alive = 0; // destroy object
            }
            Rectangle go = gameobject_rectangle(&field->objects[i]);

            // COLLISION WITH ENEMIES
            for(int j = 0; j < MAX_ENEMIES; j++) {
                if (field->enemies[j].alive == 1) {
                    Rectangle enemy = enemy_rectangle(&field->enemies[j]);
                    if (rectangle_collide(&go, &enemy)) {
                        if (field->objects[i].owner != 2) {
                            field->objects[i].alive = 0; // destroy go
                            field->enemies[j].alive = 0; // destroy enemy
                            Player *a = field->objects[i].author;
                            a->score += ENEMY_DEFEAT_SCORE;

                            if (rand() % HEALTH_PACK_CHANCE == 1) {
                                int index = field_gameobjects_find_space(field);
                                gameobject_spawn(&field->objects[index], &field->enemies[j], 2, 2); // spawn healthpack
                            }
                        }
                    }
                }
            }

            // COLLISION WITH PLAYERS
            for(int j = 0; j < MAX_PLAYERS; j++) {
                Rectangle player = player_rectangle(&field->players[j]);
                if (rectangle_collide(&go, &player)) {
                    switch(field->objects[i].type) {
                        case 1:
                            // Situation: bullet arrived at player
                            if (field->objects[i].owner == 2) {
                                field->objects[i].alive = 0;
                                field->players[j].health -= 10;
                                if (field->players[j].health == 0) {
                                    player_dead(&field->players[j]);
                                }
                            }
                            break;
                        case 2:
                            field->objects[i].alive = 0;
                            field->players[j].health += HEALTH_PACK_GAIN;
                            // Situation: health arrived at player
                            break;
                        default:
                            break;
                    }
                }
            }

        }
    }
}

void game_update_enemies(Field* field) {
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if (field->enemies[i].alive == 1) {
            enemy_move(&field->enemies[i]);
            if (rand() % ENEMY_SHOOT_CHANCE == 1) {
                int index = field_gameobjects_find_space(field);
                if (index != -1) {
                    gameobject_spawn(&field->objects[index], &field->enemies[i], 2, 1); // spawn bullet
                }
            }
            if(field->enemies[i].y > WORLD_HEIGHT) {
                field->enemies[i].alive = 0;
            }
            Rectangle enemy = enemy_rectangle(&field->enemies[i]);

            // COLLISION WITH PLAYERS
            for(int j = 0; j < MAX_PLAYERS; j++) {
                if (!field->players[j].is_dead) {
                    Rectangle player = player_rectangle(&field->players[j]);
                    if (rectangle_collide(&enemy, &player)) {
                        field->enemies[i].alive = 0;
                        field->players[j].health -= 10;
                        if (field->players[j].health == 0) {
                            player_dead(&field->players[j]);
                        }
                    }
                }
            }

        }
    }

    if (field_enemies_count(field) < MAX_SPAWNED_ENEMIES) {
        if (rand() % ENEMY_SPAWN_CHANCE == 1) {
            int write_index = field_enemies_find_space(field);
            if (write_index != -1) {
                const int x = rand_between(32, WORLD_WIDTH - 32);
                enemy_spawn(&field->enemies[write_index], 1, x);
            }
        }
    }
}