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

void Movement(Player *player, Application* app)
{

    player->position.x += player->velocity.x * 0.5;
    //printf("%d\t",player->position.x);
    if (player->position.x >= app->size.x - player->size.x)
    {
        player->position.x = app->size.x - player->size.x;
    }

    if (player->position.x <= 0)
    {
        player->position.x = 0;
    }
}

void InputEvent(Application *app, Player *player)
{
    while (SDL_PollEvent(&app->event))
    {
        if (app->event.type == SDL_QUIT)            //quit
        {
            app->running = false;
        }

        else if (app->event.type == SDL_KEYDOWN)
        {
            if (app->event.key.keysym.sym == SDLK_LEFT)     //do leva
                player->controls[LEFT] = true;

            if (app->event.key.keysym.sym == SDLK_RIGHT)    //do prava
                player->controls[RIGHT] = true;

            if (app->event.key.keysym.sym == SDLK_r)        //Restart, vykoná se funkce
                player->controls[RESTART] = true;

            if (app->event.key.keysym.sym == SDLK_ESCAPE)   //Konec hry
                app->running = false;

            if (app->event.key.keysym.sym == SDLK_p)        //Pauza
                player->controls[PAUSE] = true;

            if(app->event.key.keysym.sym == SDLK_SPACE)     //boost pra pohyb
                player->controls[BOOST] = true;
            if(app->event.key.keysym.sym == SDLK_UP)        //Start Hry
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

            if(app->event.key.keysym.sym == SDLK_SPACE)
                player->controls[BOOST] = false;

            //if(app->event.key.keysym.sym == SDLK_UP)
            //    player->controls[START] = false;
        }
    }
    UpdateVelocity(player);
    UpdateSpeed(player);
}

void UpdateVelocity(Player* player)
{
    //printf("Levá:%d\nPravá:%d\n",player->controls[1],player->controls[0]);
    //printf("Levá:%d\nPravá:%d\n",player->controls[LEFT],player->controls[RIGHT]); //0 1
    if(player->controls[LEFT])
        {
            player->velocity.x = -player->speed;
            return;
        }

    else if(player->controls[RIGHT])
    {
        player->velocity.x = player->speed;
        return;
    }

    else
        player->velocity.x = 0;
    return;
}

void UpdateSpeed(Player* player)
{
    if(player->controls[BOOST])
        player->speed =DEFAULT_SPEED + 8;
    else
        player->speed = DEFAULT_SPEED;
}

void CheckHealth(Player* player)
{
    if(player->health <= 0)
        player->controls[RESTART] = true;
}

void RestartPlayer(Player* player)
{
    player->health = 3;
    player->score = 0;
    player->position = (Vec2){ WINDOW_WIDTH / 2 - player->size.x / 2, WINDOW_HEIGHT - 50};
    
}
