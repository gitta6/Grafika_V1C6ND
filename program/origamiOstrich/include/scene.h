#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include <obj/model.h>
#include "GL/gl.h"
#include "ostrich.h"
#include "labyrinth.h"
#include "you_won.h"
#include "texture.h"
#include <stdbool.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>


typedef struct Scene
{
    Material material;
    Ostrich ostrich;
    Labyrinth labyrinth;
    float lightingLevel;
    GLuint desert_texture_id;
    bool showInstructions;
    bool showWinScene;
    GLuint instructions_texture_id; 
    bool spectateMode;
    YouWon youWon;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set lighting.
 */
void set_lighting(float lightingLevel);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/*
* Draw the desert.
*/
void draw_desert(const Scene* scene);

/*
* Draw the ostrich.
*/
void draw_ostrich(const Scene* scene);

/*
* Show instructions.
*/
void instructions(GLuint texture);

/*
* Draw the "you won" object.
*/
void draw_you_won(const Scene* scene);

#endif /* SCENE_H */
