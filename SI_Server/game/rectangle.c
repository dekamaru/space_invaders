#include "rectangle.h"

Rectangle enemy_rectangle(Enemy *e) {
    Rectangle result;
    result.x = e->x;
    result.y = e->y;
    result.w = e->width;
    result.h = e->height;
    return result;
}

Rectangle player_rectangle(Player *e) {
    Rectangle result;
    result.x = e->x;
    result.y = e->y;
    result.w = e->width;
    result.h = e->height;
    return result;
}

Rectangle gameobject_rectangle(GameObject *e) {
    Rectangle result;
    result.x = e->x;
    result.y = e->y;
    result.w = e->width;
    result.h = e->height;
    return result;
}

int rectangle_collide(Rectangle *r1, Rectangle *r2) {
    if (r1->x < r2->x + r2->w &&
        r1->x + r1->w > r2->x &&
        r1->y < r2->y + r2->h &&
        r1->h + r1->y > r2->y) {
        return 1;
    }
        return 0;
}
