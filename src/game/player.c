#include "../../header/Game/player.h"

void DrawPlayer(Player *player, SDL_Renderer *renderer)
{
    player->rect.x = player->position.x;
    player->rect.y = player->position.y;
    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
}

void DestroyPlayer(Player *player)
{
    SDL_DestroyTexture(player->texture);
    free(player);
}

void Movement(Player *player, Application *app)
{
    player->position.x += player->velocity.x * 0.5;
    player->position.x = player->position.x >= app->size.x - player->size.x ? app->size.x - player->size.x : player->position.x; // pravá stěna
    player->position.x = player->position.x <= 0 ? 0 : player->position.x;                                                       // levá stěna
}

void InputEvent(Application *app, Player *player)
{
    while (SDL_PollEvent(&app->event))
    {
        if (app->event.type == SDL_QUIT) // quit
            app->running = false;
        else if (app->event.type == SDL_KEYDOWN)
        {
            if (app->event.key.keysym.sym == SDLK_LEFT) // do leva
                player->controls[LEFT] = true;

            if (app->event.key.keysym.sym == SDLK_RIGHT) // do prava
                player->controls[RIGHT] = true;

            if (app->event.key.keysym.sym == SDLK_r) // Restart, vykoná se funkce
                player->controls[RESTART] = true;

            if (app->event.key.keysym.sym == SDLK_ESCAPE) // Konec hry
                app->running = false;

            if (app->event.key.keysym.sym == SDLK_p) // Pauza
                player->controls[PAUSE] = true;

            if (app->event.key.keysym.sym == SDLK_SPACE) // boost pra pohyb
                player->controls[BOOST] = true;

            if (app->event.key.keysym.sym == SDLK_UP) // Start Hry
                player->controls[START] = true;
        }

        else if (app->event.type == SDL_KEYUP)
        {
            if (app->event.key.keysym.sym == SDLK_LEFT)
                player->controls[LEFT] = false;

            if (app->event.key.keysym.sym == SDLK_RIGHT)
                player->controls[RIGHT] = false;

            if (app->event.key.keysym.sym == SDLK_r)
                player->controls[RESTART] = false;

            if (app->event.key.keysym.sym == SDLK_p)
                player->controls[PAUSE] = false;

            if (app->event.key.keysym.sym == SDLK_SPACE)
                player->controls[BOOST] = false;
        }
    }
    UpdateVelocity(player);
    UpdateSpeed(player);
}

void UpdateVelocity(Player *player)
{
    if (player->controls[LEFT])
    {
        player->velocity.x = -player->speed;
        return;
    }
    else if (player->controls[RIGHT])
    {
        player->velocity.x = player->speed;
        return;
    }
    else
        player->velocity.x = 0;
    return;
}

void UpdateSpeed(Player *player)
{
    player->speed = player->controls[BOOST] ? DEFAULT_SPEED + 8 : DEFAULT_SPEED;
}

void CheckHealth(Player *player)
{
    player->controls[RESTART] = player->health <= 0;
}

void RestartPlayer(Player *player)
{
    player->health = 3;
    player->score = 0;
    player->position = (Vec2){WINDOW_WIDTH / 2 - player->size.x / 2, WINDOW_HEIGHT - 50};
}

void SetPLayerName(Player *player, char *name, int argc)
{
    player->name = argc == 2 ? name : "Player";
}


void WriteScore(Player *player)
{
    char *score = malloc(sizeof(char) * 5);
    sprintf(score,"%d", player->score);
    FILE* file = fopen("../score.txt", "a");
    fputs(player->name, file);
    fputs(",", file);
    fputs(score, file);
    fputs("\n\0", file);
    fclose(file);
    free(score);

}
