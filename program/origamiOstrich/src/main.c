#include "app.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>

/**
 * Main function
 */
int main(int argc, char *argv[])
{
    App app;

    init_app(&app, 1280, 720);
    while (app.is_running)
    {
        handle_app_events(&app);
        update_app(&app);
        render_app(&app);
    }

    // Model model;
    // load_model(&model, "./assets/models/origamiOstrich.obj");
    // print_model_info(&model);
    destroy_app(&app);

    return 0;
}
