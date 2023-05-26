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

/**
 * Set the position of the ostrich.
 */
void set_ostrich_pos(Ostrich *ostrich, vec3 newPos);

/**
 * Set the speed of the ostrich.
 */
void set_ostrich_speed(Ostrich *ostrich, double speed);

/**
 * Set the side speed of the ostrich.
 */
void set_ostrich_side_speed(Ostrich *ostrich, double speed);

/**
 * Set the vertical speed of the ostrich.
 */
void set_ostrich_vertical_speed(Ostrich *ostrich, double speed);

/**
 * Move the ostrich.
 */
void move_ostrich(Ostrich *ostrich, double time);

/**
 * Rotate the ostrich.
 */
void rotate_ostrich(Ostrich *ostrich, double horizontal);

#endif /*OSTRICH_H*/