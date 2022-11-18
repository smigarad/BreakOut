#include "../header/main.h"

int main(int argc, char *argv[])
{
    // konstruktory a inicializace SDL
    Application *app = ApplicationConstructor();
    Player *player = PlayerConstructor(app->renderer);
    Ball *ball = BallConstructor(app->renderer);
    Background *background = BackgroundConstructor(app->renderer);
    int n = 20;
    Block **blocks = BlocksConstructor(n, app->renderer);
    Font *fontScore = FontConstructor();
    Font *fontLives = FontConstructor();
    Font *fontGame = FontConstructor();

    bool fontsGameWasUsed;
    // hlavní smyčka
    while (app->running)
    {
        app->frameStart = SDL_GetTicks();
        if (player->health != 0)
        {
            if (player->start) // Pokud hra začala
            {
                if(CheckWin(blocks,n))                             //výhra
                    DrawPlayerWin(app->renderer, fontGame, player,app);
                    
                else
                {
                    Movement(player, app);   // pohyb hráče
                    // UpdateVelocity(player);        // speed; - speed
                    // UpdateSpeed(player);           // default nebo vyšší když se zmáčkne space
                    UpdateBall(ball, player, app); // pohyb míčku
                    BlocksCollision(n, ball, blocks, player);

                    DrawBackground(app->renderer, background);           // vykreslení pozadí
                    DrawScore(app->renderer, fontScore, player->score);  // vykreslení skóre
                    DrawLives(player->health, app->renderer, fontLives); // vykreslení životů
                    DrawBlocks(blocks, n, app->renderer);                // vykreslení bloků
                    DrawLine(app->renderer, player);                     // vykreslení čáry
                    DrawPlayer(player, app->renderer);                   // vykreslení hráče
                    DrawBall(ball, app->renderer);                       // vykreslení míčku
                }
            }
        }
        
        else // konec hry
            DrawGameOver(app, fontGame, player);

        if (!player->start || player->controls[RESTART]) // Začátek hry a restart
        {
            DrawOpeningScene(app, fontGame);
            RestartPlayer(player);
            if (player->controls[START])
            {
                player->start = true;
                player->controls[START] = false;
            }
            if (player->controls[RESTART])
            {
                player->start = false;
                RestartBlocks(blocks, n);
            }
        }

        InputEvent(app, player); // IMPUT
        Frames(app);                      // FPS a jejich cap
        SDL_RenderPresent(app->renderer); // render
    }

    // Delokace paměti a ukončení SDL
    for (int i = 0; i < n; i++)
    {
        DestroyBlock(blocks[i]);
    }
    free(blocks);
    DestroyFont(fontScore);
    DestroyFont(fontLives);
    DestroyFont(fontGame);
    DestroyPlayer(player);
    DestroyBall(ball);
    DestroyBackground(background);

    DestroyApp(app);
    return 0;
}
