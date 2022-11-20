#include "InitRender/application.h"
#include "Game/ball.h"
#include "Game/block.h"
#include "Game/player.h"
#include "InitRender/draw.h"
#include <SDL2/SDL_ttf.h>
#include <time.h>
#pragma once

Player *PlayerConstructor(SDL_Renderer *renderer);
Ball *BallConstructor(SDL_Renderer *renderer);
Block *BlockConstructor(SDL_Renderer *renderer);
Block **BlocksConstructor(int n, SDL_Renderer *renderer, SDL_Texture **textures);
SDL_Texture **SetTextures(SDL_Renderer *renderer);
Block *BlocksConstructorArray(int n, SDL_Renderer *renderer);
Block *BlocksConstructorStatic(int n, SDL_Renderer *renderer);
Font *FontConstructor();
Background *BackgroundConstructor(SDL_Renderer *renderer);
Application *ApplicationConstructor();
