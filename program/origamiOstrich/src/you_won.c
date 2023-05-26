#include "you_won.h"

void init_you_won(YouWon *youWon)
{
    load_model(&(youWon->model), "assets/models/youWon.obj");
    youWon->you_won_texture_id = load_texture("assets/textures/goldTexture.jpg");

    youWon->pos.x = 0.0;
    youWon->pos.y = 0.0;
    youWon->pos.z = 0.0;

    youWon->rotation.x = 0.0;
    youWon->rotation.y = 0.0;
    youWon->rotation.z = 0.0;

    youWon->speed.x = 0.0;
    youWon->speed.y = 0.0;
    youWon->speed.z = 0.0;

    youWon->forward = false;
    youWon->backward = false;
    youWon->left = false;
    youWon->right = false;
}

void set_you_won_pos(YouWon *youWon, vec3 newPos)
{
    youWon->pos.x += newPos.x;
    youWon->pos.y += newPos.y;
    youWon->pos.z += newPos.z;
}

void set_you_won_speed(YouWon *youWon, double speed)
{
    youWon->speed.y = -speed;
}

void set_you_won_side_speed(YouWon *youWon, double speed)
{
    youWon->speed.x = speed;
}

void set_you_won_vertical_speed(YouWon *youWon, double speed)
{
    youWon->speed.z = speed;
}

void move_you_won(YouWon *youWon, double time)
{
    youWon->pos.x += youWon->speed.x * time;
    youWon->pos.y += youWon->speed.y * time;
    youWon->pos.z += youWon->speed.z * time;
}

void rotate_you_won(YouWon *youWon, double horizontal)
{
    youWon->rotation.y += horizontal;

    if (youWon->rotation.z < 0)
    {
        youWon->rotation.z += 360.0;
    }

    if (youWon->rotation.z > 360.0)
    {
        youWon->rotation.z -= 360.0;
    }

    if (youWon->rotation.x < 0)
    {
        youWon->rotation.x += 360.0;
    }

    if (youWon->rotation.x > 360.0)
    {
        youWon->rotation.x -= 360.0;
    }
}

void levitate_you_won(YouWon *youWon)
{
    double current_time = (double)SDL_GetTicks() / 1000;
    printf("%lf\n", current_time);
    youWon->pos.z = sin(current_time) / 2;
    youWon->rotation.y += current_time / 30;
}