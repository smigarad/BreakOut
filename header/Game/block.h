#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../InitRender/application.h"
#pragma once

#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 20
typedef struct Block{
    SDL_Texture *texture;
    SDL_Rect rect;
    Vec2 position;
    Vec2 size;
    bool isDestroyed;
} Block;

void DrawBlock(Block* block, SDL_Renderer* renderer);
char* ChooseTexture();
void DestroyBlock(Block* block);
void DrawBlocks(Block** blocks, int n, SDL_Renderer* renderer);
//void DrawBlocksArray(Block* blocks, int n, SDL_Renderer* renderer);
void DestroyBlocks(Block** blocks, int n);
void RestartBlocks(Block** blocks, int n);
bool CheckWin(Block** blocks, int n);