#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App *app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Origami Ostrich",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL)
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0)
    {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL)
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.0f, 0.5f, 0.8f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void set_night()
{
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
}

void set_day()
{
    glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10);
}

void handle_app_events(App *app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_KP_PLUS: // fényerő fel
                app->scene.lightingLevel += 0.2f;
                set_lighting(app->scene.lightingLevel);
                break;
            case SDL_SCANCODE_KP_MINUS: // fényerő le
                app->scene.lightingLevel -= 0.2f;
                set_lighting(app->scene.lightingLevel);
                break;
            case SDL_SCANCODE_W:
                if (app->scene.spectateMode)
                {
                    set_camera_speed(&(app->camera), 3);
                }
                else
                {
                    set_camera_speed(&(app->camera), 3);
                    set_ostrich_speed(&(app->scene.ostrich), 3);
                    app->scene.ostrich.forward = true;
                }
                break;
            case SDL_SCANCODE_S:
                if (app->scene.spectateMode)
                {
                    set_camera_speed(&(app->camera), -3);
                }
                else
                {
                    set_camera_speed(&(app->camera), -3);
                    set_ostrich_speed(&(app->scene.ostrich), -3);
                    app->scene.ostrich.backward = true;
                }
                break;
            case SDL_SCANCODE_A:
                if (app->scene.spectateMode)
                {
                    set_camera_side_speed(&(app->camera), 3);
                }
                else
                {
                    set_camera_side_speed(&(app->camera), 3);
                    set_ostrich_side_speed(&(app->scene.ostrich), 3);
                    app->scene.ostrich.left = true;
                }
                break;
            case SDL_SCANCODE_D:
                if (app->scene.spectateMode)
                {
                    set_camera_side_speed(&(app->camera), -3);
                }
                else
                {
                    set_camera_side_speed(&(app->camera), -3);
                    set_ostrich_side_speed(&(app->scene.ostrich), -3);
                    app->scene.ostrich.right = true;
                }

                break;
            case SDL_SCANCODE_Q:
                app->camera.speed.z = 3;
                break;
            case SDL_SCANCODE_E:
                app->camera.speed.z = -3;
                break;
            case SDL_SCANCODE_N: // night
                set_night();
                app->scene.lightingLevel = 0.5f;
                set_lighting(app->scene.lightingLevel);
                glEnable(GL_FOG);
                glFogf(GL_FOG_DENSITY, 0.5f);
                break;
            case SDL_SCANCODE_M: // day
                set_day();
                app->scene.lightingLevel = 3.0f;
                set_lighting(app->scene.lightingLevel);
                glEnable(GL_FOG);
                glFogf(GL_FOG_DENSITY, 0.10f);
                break;

                // o. movement (if it's separated from camera movement)
                /*
                case SDL_SCANCODE_UP:
                    set_ostrich_speed(&(app->scene.ostrich), 3);
                    app->scene.ostrich.forward = true;
                    break;
                case SDL_SCANCODE_DOWN:
                    set_ostrich_speed(&(app->scene.ostrich), -3);
                    app->scene.ostrich.backward = true;
                    break;
                case SDL_SCANCODE_LEFT:
                    set_ostrich_side_speed(&(app->scene.ostrich), 3);
                    app->scene.ostrich.left = true;
                    break;
                case SDL_SCANCODE_RIGHT:
                    set_ostrich_side_speed(&(app->scene.ostrich), -3);
                    app->scene.ostrich.right = true;
                    break;
                    */
                // end of o. movement
            case SDL_SCANCODE_F5:
                if (app->scene.spectateMode)
                {
                    app->scene.spectateMode = false;
                }
                else
                {
                    app->scene.spectateMode = true;
                }
                break;
                break;

            case SDL_SCANCODE_F1:
                if (app->scene.showInstructions) // instructions
                {
                    app->scene.showInstructions = false;
                    glFrustum(
                        -.08, .08,
                        -.06, .06,
                        .1, 6000);
                }
                else
                {
                    app->scene.showInstructions = true;
                }
                break;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                if (app->scene.spectateMode)
                {
                    set_camera_speed(&(app->camera), 0);
                }
                else
                {
                    set_camera_speed(&(app->camera), 0);
                    set_ostrich_speed(&(app->scene.ostrich), 0);
                    app->scene.ostrich.forward = false;
                    app->scene.ostrich.backward = false;
                    app->scene.ostrich.left = false;
                    app->scene.ostrich.right = false;
                }
                break;
            case SDL_SCANCODE_S:
                if (app->scene.spectateMode)
                {
                    set_camera_speed(&(app->camera), 0);
                }
                else
                {
                    set_camera_speed(&(app->camera), 0);
                    set_ostrich_speed(&(app->scene.ostrich), 0);
                    app->scene.ostrich.forward = false;
                    app->scene.ostrich.backward = false;
                    app->scene.ostrich.left = false;
                    app->scene.ostrich.right = false;
                }
                break;
            case SDL_SCANCODE_A:
                if (app->scene.spectateMode)
                {
                    set_camera_side_speed(&(app->camera), 0);
                }
                else
                {
                    set_camera_side_speed(&(app->camera), 0);
                    set_ostrich_side_speed(&(app->scene.ostrich), 0);
                    app->scene.ostrich.forward = false;
                    app->scene.ostrich.backward = false;
                    app->scene.ostrich.left = false;
                    app->scene.ostrich.right = false;
                }
                break;
            case SDL_SCANCODE_D:
                if (app->scene.spectateMode)
                {
                    set_camera_side_speed(&(app->camera), 0);
                }
                else
                {
                    set_camera_side_speed(&(app->camera), 0);
                    set_ostrich_side_speed(&(app->scene.ostrich), 0);
                    app->scene.ostrich.forward = false;
                    app->scene.ostrich.backward = false;
                    app->scene.ostrich.left = false;
                    app->scene.ostrich.right = false;
                }
                break;

                // ostrich movement (if it's separated from camera movement)
                /*
            case SDL_SCANCODE_UP:
                set_ostrich_speed(&(app->scene.ostrich), 0);
                app->scene.ostrich.forward = false;
                app->scene.ostrich.backward = false;
                app->scene.ostrich.left = false;
                app->scene.ostrich.right = false;
                break;
            case SDL_SCANCODE_RIGHT:
                set_ostrich_side_speed(&(app->scene.ostrich), 0);
                app->scene.ostrich.forward = false;
                app->scene.ostrich.backward = false;
                app->scene.ostrich.left = false;
                app->scene.ostrich.right = false;
                break;
            case SDL_SCANCODE_DOWN:
                set_ostrich_speed(&(app->scene.ostrich), 0);
                app->scene.ostrich.forward = false;
                app->scene.ostrich.backward = false;
                app->scene.ostrich.left = false;
                app->scene.ostrich.right = false;
                break;
            case SDL_SCANCODE_LEFT:
                set_ostrich_side_speed(&(app->scene.ostrich), 0);
                app->scene.ostrich.forward = false;
                app->scene.ostrich.backward = false;
                app->scene.ostrich.left = false;
                app->scene.ostrich.right = false;
                break;
            */
                // end of ostrich movement
            default:
                app->camera.speed.z = 0;
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if(app->scene.spectateMode)
            {
            if (is_mouse_down)
            {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App *app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));
    move_ostrich(&(app->scene.ostrich), elapsed_time);
}

void render_app(App *app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App *app)
{
    if (app->gl_context != NULL)
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL)
    {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
