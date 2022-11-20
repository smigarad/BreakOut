#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "application.h"
#include "../Game/player.h"
#pragma once

#define BACKGROUND_WIDTH 2480 / 2.5
#define BACKGROUND_HEIGHT 3017 / 2.5
#define WATCHSTR(x) printf(#x " = %s\n", x);
typedef struct Background
{
    SDL_Texture *texture;
    SDL_Rect rect;
    Vec2 position;
    Vec2 size;
} Background;

typedef struct Font
{
    TTF_Font *font;
    SDL_Color color;
    SDL_Texture *texture;
    SDL_Rect rect;
    Vec2 position;
    Vec2 size;
} Font;

void DrawBackground(SDL_Renderer *renderer, Background *background);
void DrawScore(SDL_Renderer *renderer, Font *font, int score);
void DrawLives(int lives, SDL_Renderer *renderer, Font *fontText);
void DrawLine(SDL_Renderer *renderer, Player *player);
void DrawText(SDL_Renderer *renderer, Font *font, char *text, int x, int y);
void DrawGameOver(Application *app, Font *font, Player *player);
void DestroyFont(Font *font);
void DrawOpeningScene(Application *app, Font *font);
void DrawPlayerWin(SDL_Renderer *renderer, Font *font, Player *player, Application *app);
void DestroyBackground(Background *background);
