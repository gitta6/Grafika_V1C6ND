#include "scene.h"
#include "labyrinth.h"
#include "ostrich.h"
#include <GL/gl.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene *scene)
{
    scene->desert_texture_id = load_texture("./assets/textures/sand2.jpg");
    init_ostrich(&(scene->ostrich));
    init_labyrinth(&(scene->labyrinth));

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 0.9;
    scene->material.diffuse.green = 0.1;
    scene->material.diffuse.blue = 0.5;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 50.0;

    scene->lightingLevel = 1.5f;
    set_lighting(scene->lightingLevel);

    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 0.02f);

    scene->showInstructions = false;
    scene->instructions_texture_id = load_texture("assets/textures/instructions.jpg");

    /*
    scene->showWinScene = false;
    scene->instructions_texture_id = load_texture(" ");
    */

    scene->spectateMode = false;
}

void set_lighting(float lightingLevel)
{
    float ambient_light[] = {1.0, 1.0, 1.0, 1.0f};
    float diffuse_light[] = {lightingLevel, lightingLevel, lightingLevel, 1.0f};
    float specular_light[] = {0.0, 0.0, 0.0, 1.0f};
    float position[] = {0.0f, 10.0f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene)
{
    if (scene->ostrich.pos.z < 0)
    {
        scene->ostrich.pos.z += 0.09;
    }
}

void render_scene(const Scene *scene)
{
    // glDisable(GL_LIGHTING);

    set_lighting(scene->lightingLevel);
    set_material(&(scene->material));
    // glDisable(GL_TEXTURE);
    glPushMatrix();
    glDisable(GL_LIGHTING);
    draw_desert(scene);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    // glEnable(GL_TEXTURE);

    // glDisable(GL_TEXTURE);
    glPushMatrix();
    glTranslatef(scene->ostrich.pos.x, scene->ostrich.pos.y, scene->ostrich.pos.z);
    glVertex3f(scene->ostrich.pos.x, scene->ostrich.pos.y, scene->ostrich.pos.z);
    draw_ostrich(scene);
    glPopMatrix();
    // glEnable(GL_TEXTURE);

    glPushMatrix();
    glDisable(GL_TEXTURE);
    glDisable(GL_LIGHTING);
    draw_labyrinth(scene);
    glEnable(GL_TEXTURE);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix();
    glDisable(GL_LIGHTING);
    if (scene->showInstructions)
    {
        instructions(scene->instructions_texture_id);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // win scene
    /*
    glPushMatrix();
    glDisable(GL_LIGHTING);
    if (scene->showWinScene)
    {
        win_scene(scene->instructions_texture_id);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
    */
}

void instructions(GLuint texture)
{
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glEnable(GL_DEPTH_TEST);
}

/*
void win_scene(GLuint texture)
{
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glEnable(GL_DEPTH_TEST);
}
*/

void draw_desert(const Scene *scene)
{
    glBindTexture(GL_TEXTURE_2D, scene->desert_texture_id);
    glBegin(GL_QUADS);
    glPushMatrix();
    for (int i = -100; i < 100; i++)
    {
        {
            for (int j = -100; j <= 100; j++)
            {
                glTexCoord2f(0, 1);
                glVertex3f(j, i, 0);

                glTexCoord2f(1, 1);
                glVertex3f(j + 1, i, 0);

                glTexCoord2f(1, 0);
                glVertex3f(j + 1, i + 1, 0);

                glTexCoord2f(0, 0);
                glVertex3f(j, i + 1, 0);
            }
        }
    }
    glPopMatrix();
    glEnd();
}

void draw_ostrich(const Scene *scene)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->ostrich.texture_id);
    glScalef(0.1, 0.1, 0.1);
    glRotatef(90, 1, 0, 0);
    glRotatef(scene->ostrich.rotation.y, 0, 1, 0);
    draw_model(&(scene->ostrich.model));
    glPopMatrix();
}

void draw_labyrinth(const Scene *scene)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->labyrinth.labyrinth_texture_id);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.9, 0.9, 0.9, 0.95);
    glScalef(3.0, 3.0, 3.0);
    glRotatef(90, 1, 0, 0);
    glRotatef(270, 0, 1, 0);
    draw_model(&(scene->labyrinth.model));
    glDisable(GL_BLEND);
    glPopMatrix();
}