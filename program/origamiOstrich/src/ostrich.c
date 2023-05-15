#include "ostrich.h"
#include "texture.h"

void init_ostrich(Ostrich *ostrich)
{
    load_model(&(ostrich->model), "assets/models/origamiOstrich.obj");
    // ostrich->texture_id = load_texture("assets/textures/paperTexture.jpg");

    ostrich->pos.x = 0.0;
    ostrich->pos.y = -3.0;
    ostrich->pos.z = 0.1;

    ostrich->speed.x = 0.0;
    ostrich->speed.y = 0.0;
    ostrich->speed.z = 0.0;

    ostrich->forward = false;
    ostrich->backward = false;
    ostrich->left = false;
    ostrich->right = false;

    ostrich->forward = false;
    ostrich->backward = false;
}

void set_ostrich_pos(Ostrich *ostrich, vec3 newPos)
{
    ostrich->pos.x += newPos.x;
    ostrich->pos.y += newPos.y;
    ostrich->pos.z += newPos.z;
}

void set_ostrich_speed(Ostrich *ostrich, double speed)
{
    ostrich->speed.y = -speed;
}

void set_ostrich_side_speed(Ostrich *ostrich, double speed)
{
    ostrich->speed.x = speed;
}

void set_ostrich_vertical_speed(Ostrich *ostrich, double speed)
{
    ostrich->speed.z = speed;
}

void move_ostrich(Ostrich *ostrich, double time)
{
    ostrich->pos.x += ostrich->speed.x * time;
    ostrich->pos.y += ostrich->speed.y * time;
    ostrich->pos.z += ostrich->speed.z * time;
}
