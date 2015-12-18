#include "field.h"

int field_enemies_count(Field *f) {
    int c = 0;
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if (f->enemies[i].alive == 1) c++;
    }
    return c;
}

int field_enemies_find_space(Field *f) {
    for(int i = 0; i < MAX_ENEMIES; i++) {
        if (f->enemies[i].alive == 0) return i;
    }
}
