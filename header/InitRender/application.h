#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
#define WATCH(x) printf(#x " = %d\n", x);

typedef struct
{ // 2D vektor pro definování pozic a velikostí
    int x;
    int y;
} Vec2;

typedef struct
{ // applikace obsahující windows, renderer, event a frames a velikost okna
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool running;
    int frameStart;
    int frameTime;
    Vec2 size;
} Application;

void DestroyApp(Application *app); // Ukončení aplikace
void Frames(Application *app);     // Omezení FPS