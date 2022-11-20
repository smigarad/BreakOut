#include "../../header/InitRender/application.h"

void DestroyApp(Application* app)
{
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
    TTF_Quit();
    free(app);
}

void Frames(Application* app)
{
    app->frameTime = SDL_GetTicks() - app->frameStart;
    if (FRAME_TARGET_TIME > app->frameTime)
        SDL_Delay(FRAME_TARGET_TIME - app->frameTime);
}
