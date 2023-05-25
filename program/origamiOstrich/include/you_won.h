#ifndef YOU_WON_H
#define YOU_WON_H

#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"
#include "utils.h"
#include "camera.h"
#include <stdbool.h>

typedef struct YouWon
{
    Model model;
    vec3 pos;
    GLuint you_won_texture_id;
    vec3 rotation;
    vec3 rotationSpeed;
    vec3 speed;
    bool forward;
    bool backward;
    bool left;
    bool right;
} YouWon;

/**
 * Initialize the "you won" text.
 */
void init_you_won(YouWon *youWon);

/*
* Set the position of the "you won" text.
*/
void set_you_won_pos(YouWon *youWon, vec3 newPos);

void set_you_won_speed(YouWon *youWon, double speed);

void set_you_won_side_speed(YouWon *youWon, double speed);

void set_you_won_vertical_speed(YouWon *youWon, double speed);

void move_you_won(YouWon *youWon, double time);

void rotate_you_won(YouWon *youWon, double horizontal);

void levitate_you_won(YouWon *youWon);

#endif /*YOU_WON_H*/