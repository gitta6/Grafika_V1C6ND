#include "labyrinth.h"

void init_labyrinth(Labyrinth *labyrinth)
{
    load_model(&(labyrinth->model), "assets/models/labyrinth.obj");
    labyrinth->pos.x = 20.0;
    labyrinth->pos.y = 5.0;
    labyrinth->pos.z = -30.0;
}