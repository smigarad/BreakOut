#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../InitRender/application.h"
#pragma once


#define PLAYER_HEIGHT 15
#define PLAYER_WIDTH 100
#define DEFAULT_SPEED 10
enum Movement
{
    
    RIGHT,  //0
    LEFT,    //1
    RESTART,
    PAUSE,
    BOOST,
    START

};

typedef struct Player
{
    int health;         //životy
    u_short speed;      //rychlost
    SDL_Texture* texture;   //textura objektu
    SDL_Rect rect;          //sdl objekt
    Vec2 position;          //pozice
    Vec2 size;              //velikost
    Vec2 velocity;          // + nebo - rychlost
    bool controls[6];       //ovládání
    int score;              //skóre
    bool start;             //Zda li zapnul hru
    char* name;             //Jméno hráče
} Player;

void DrawPlayer(Player* player, SDL_Renderer* renderer);
void InputEvent(Application* app, Player* Player);  //Dávám ho zde a ne do application, protože je zde lehčí manipulace.
void Movement(Player* player, Application* app);
void DestroyPlayer(Player* player);
void UpdateVelocity(Player* player);
void UpdateSpeed(Player* player);
void RestartPlayer(Player* player);