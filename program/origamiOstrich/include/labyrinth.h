#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"
#include "utils.h"
#include "camera.h"
#include <stdbool.h>

typedef struct Labyrinth
{
    Model model;
    vec3 pos;
    GLuint labyrinth_texture_id
} Labyrinth;

/**
 * Initialize the labyrinth. 
 */
void init_labyrinth(Labyrinth *labyrinth);

#endif /*LABYRINTH_H*/