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
    vec3 rotation;
} YouWon;

/**
 * Initialize the "you won" object.
 */
void init_you_won(YouWon *youWon);

/**
 * Levitate the "you won" object.
 */
void levitate_you_won(YouWon *youWon);

#endif /*YOU_WON_H*/