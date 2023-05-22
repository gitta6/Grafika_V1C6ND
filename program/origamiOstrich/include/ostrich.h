#ifndef OSTRICH_H
#define OSTRICH_H

#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"
#include "utils.h"
#include "camera.h"
#include <stdbool.h>

typedef struct Ostrich
{
    GLuint texture_id;
    Model model;
    vec3 pos;
    vec3 speed;
    vec3 rotation;
    bool forward;
    bool backward;
    bool left;
    bool right;
} Ostrich;

/**
 * Initialize the ostrich.
 */
void init_ostrich(Ostrich *ostrich);

void set_ostrich_pos(Ostrich *ostrich, vec3 newPos);

void set_ostrich_speed(Ostrich *ostrich, double speed);

void set_ostrich_side_speed(Ostrich *ostrich, double speed);

void set_ostrich_vertical_speed(Ostrich *ostrich, double speed);

void move_ostrich(Ostrich *ostrich, double time);

void rotate_ostrich(Ostrich *ostrich, double horizontal);

void rotate_ostrich_right(Ostrich *ostrich);

void rotate_ostrich_left(Ostrich *ostrich);

#endif /*OSTRICH_H*/