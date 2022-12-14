#include "../../header/InitRender/draw.h"

void DrawBackground(SDL_Renderer *renderer, Background *background) // Vykresluje pozadí
{
    SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);
}

void DestroyBackground(Background *background) // Uvolňuje texture a delokuje pamět
{
    SDL_DestroyTexture(background->texture);
    free(background);
}

void DrawScore(SDL_Renderer *renderer, Font *font, int score) // Ukazuje skóre
{
    char scoreText[10];
    sprintf(scoreText, "%d", score);
    SDL_Surface *surface = TTF_RenderText_Solid(font->font, scoreText, font->color);
    font->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(font->texture, NULL, NULL, &font->rect.w, &font->rect.h); // scaling textury do velikosti rect
    SDL_RenderCopy(renderer, font->texture, NULL, &font->rect);
}

void DrawLives(int lives, SDL_Renderer *renderer, Font *fontText)
{
    char text[11] = "Lives: ";
    char livesText2[3];
    sprintf(livesText2, "%d", lives);
    strcat(text, livesText2);
    SDL_Surface *surface = TTF_RenderText_Solid(fontText->font, text, fontText->color);
    fontText->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(fontText->texture, NULL, NULL, &fontText->rect.w, &fontText->rect.h); // scaling textury do velikosti rect
    WATCH(fontText->rect.w);
    WATCH(fontText->rect.h);
    fontText->rect.x = fontText->position.x = WINDOW_WIDTH - fontText->rect.w - 10;
    fontText->rect.y = fontText->position.y = 10;
    SDL_RenderCopy(renderer, fontText->texture, NULL, &fontText->rect);
}

void DestroyFont(Font *font) // Uvolňuje texturu, delokuje pamět a zavírá font
{
    SDL_DestroyTexture(font->texture);
    TTF_CloseFont(font->font);
    free(font);
}

void DrawLine(SDL_Renderer *renderer, Player *player)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0, player->position.y + player->size.y / 2, WINDOW_WIDTH, player->position.y + player->size.y / 2);
}

void DrawGameOver(Application *app, Font *font, Player *player)
{
    SDL_Rect rect = {0, 0, app->size.x, app->size.y};
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(app->renderer, &rect);

    DrawText(app->renderer, font, "GAME OVER!", app->size.x / 2 - font->size.x / 2 - 50, app->size.y / 2 - 100);
    DrawText(app->renderer, font, "Press R to restart", app->size.x / 2 - font->size.x / 2 - 100, app->size.y / 2 + font->size.y - 100);
    DrawText(app->renderer, font, "Press ESC to exit", app->size.x / 2 - font->size.x / 2 - 90, app->size.y / 2 + font->size.y * 2 - 100);
    DrawText(app->renderer, font, "Player: ", app->size.x / 2 - font->size.x / 2 - 120, app->size.y / 2 + font->size.y * 4 - 100);
    DrawText(app->renderer, font, player->name, app->size.x / 2 - font->size.x / 2 - 20, app->size.y / 2 + font->size.y * 4 - 100);
    DrawText(app->renderer, font, "Score: ", app->size.x / 2 - font->size.x / 2 - 120, app->size.y / 2 + font->size.y * 5 - 100);
    char *scoreText = malloc(sizeof(char) * 10);
    sprintf(scoreText, "%d", player->score);
    DrawText(app->renderer, font, scoreText, app->size.x / 2 - font->size.x / 2 - 20, app->size.y / 2 + font->size.y * 5 - 100);
    free(scoreText);
}

void DrawPlayerWin(SDL_Renderer *renderer, Font *font, Player *player, Application *app)
{
    SDL_Rect rect = {0, 0, app->size.x, app->size.y};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    DrawText(renderer, font, "YOU WIN!", app->size.x / 2 - font->size.x / 2 - 40, app->size.y / 2 - 100);
    DrawText(renderer, font, "Press R to restart", app->size.x / 2 - font->size.x / 2 - 100, app->size.y / 2 + font->size.y - 100);
    DrawText(renderer, font, "Press ESC to exit", app->size.x / 2 - font->size.x / 2 - 90, app->size.y / 2 + font->size.y * 2 - 100);
    DrawText(renderer, font, "Player: ", app->size.x / 2 - font->size.x / 2 - 120, app->size.y / 2 + font->size.y * 4 - 100);
    DrawText(renderer, font, player->name, app->size.x / 2 - font->size.x / 2 - 20, app->size.y / 2 + font->size.y * 4 - 100);
    DrawText(renderer, font, "Score: ", app->size.x / 2 - font->size.x / 2 - 120, app->size.y / 2 + font->size.y * 5 - 100);
    char scoreText[10];
    sprintf(scoreText, "%d", player->score);
    DrawText(renderer, font, scoreText, app->size.x / 2 - font->size.x / 2 - 20, app->size.y / 2 + font->size.y * 5 - 100);
}

void DrawOpeningScene(Application *app, Font *font)
{
    SDL_Rect rect = {0, 0, app->size.x, app->size.y};
    SDL_Surface *surface = IMG_Load("../assets/MainScreen.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app->renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(app->renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    DrawText(app->renderer, font, "Welcome to Breakout!", font->size.x + 130, font->size.y + 20);
    DrawText(app->renderer, font, "Press UP - play", font->size.x + 130, font->size.y * 15);
    DrawText(app->renderer, font, "Press R - restart", font->size.x + 130, font->size.y * 16);
    DrawText(app->renderer, font, "Press Left key - left ", font->size.x + 130, font->size.y * 17);
    DrawText(app->renderer, font, "Press Right key - Right ", font->size.x + 130, font->size.y * 18);
    DrawText(app->renderer, font, "Press Space - boost ", font->size.x + 130, font->size.y * 19);
    DrawText(app->renderer, font, "Press ESC - Quit", font->size.x + 130, font->size.y * 20);
}

void DrawText(SDL_Renderer *renderer, Font *font, char *text, int x, int y)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font->font, text, font->color);
    font->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(font->texture, NULL, NULL, &font->rect.w, &font->rect.h); // scaling textury do velikosti rect
    font->rect.x = font->position.x = x;
    font->rect.y = font->position.y = y;
    SDL_RenderCopy(renderer, font->texture, NULL, &font->rect);
}
