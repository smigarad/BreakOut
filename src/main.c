#include "../header/main.h"

int main(int argc, char **argv)
{
    int n = 100; // Počet bloků
    // konstruktory a inicializace SDL
    Application *app = ApplicationConstructor();                    // Inicializace SDL a hlavní okénko
    Player *player = PlayerConstructor(app->renderer);              // Inicializace hráče
    Ball *ball = BallConstructor(app->renderer);                    // Inicializace míčku
    Background *background = BackgroundConstructor(app->renderer);  // Inicializace pozadí
    SDL_Texture **textures = SetTextures(app->renderer);            // Inicializace textur pro bloky
    Block **blocks = BlocksConstructor(n, app->renderer, textures); // Inicializace bloků
    Font *fontScore = FontConstructor();                            // Inicializace fontu pro skóre
    Font *fontLives = FontConstructor();                            // Inicializace fontu pro životy
    Font *fontGame = FontConstructor();                             // Inicializace fontu pro Game Over
    SetPLayerName(player, argv[1], argc);                           // Nastavení jména hráče
    bool writen;                                                    // Zda li bylo skóre zapsáno
    // hlavní smyčka
    while (app->running)
    {
        app->frameStart = SDL_GetTicks();
        if (player->health != 0)
        {
            if (player->start) // Pokud hra začala
            {
                if (CheckWin(blocks, n)) // výhra
                {
                    DrawPlayerWin(app->renderer, fontGame, player, app);
                    if (!writen)
                    {
                        WriteScore(player);
                        writen = true;
                    }
                }
                else
                {
                    Movement(player, app);         // pohyb hráče
                    UpdateBall(ball, player, app); // pohyb míčku
                    BlocksCollision(n, ball, blocks, player);
                    // vykreslení
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
        {
            DrawGameOver(app, fontGame, player);
            if (!writen)
            {
                WriteScore(player);
                writen = true;
            }
        }

        if (!player->start || player->controls[RESTART]) // Začátek hry a restart
        {
            writen = false;
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

        InputEvent(app, player);          // IMPUT
        Frames(app);                      // FPS a jejich cap
        SDL_RenderPresent(app->renderer); // render
    }

    // Delokace paměti a ukončení SDL
    DestroyBlocks(blocks, n);
    free(textures);
    DestroyFont(fontGame);
    DestroyFont(fontScore);
    DestroyFont(fontLives);
    DestroyPlayer(player);
    DestroyBall(ball);
    DestroyBackground(background);
    DestroyApp(app);
    return 0;
}
