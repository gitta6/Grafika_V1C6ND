#include "you_won.h"

void init_you_won(YouWon *youWon)
{
    load_model(&(youWon->model), "assets/models/youWon.obj");

    youWon->pos.x = 0.0;
    youWon->pos.y = 0.0;
    youWon->pos.z = 0.0;

    youWon->rotation.x = 0.0;
    youWon->rotation.y = 0.0;
    youWon->rotation.z = 0.0;
}

void levitate_you_won(YouWon *youWon)
{
    double current_time = (double)SDL_GetTicks() / 1000;
    youWon->pos.z = sin(current_time) / 2;
    youWon->rotation.y += current_time / 10;
}