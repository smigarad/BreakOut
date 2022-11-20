#include "../../header/Game/block.h"

void DrawBlock(Block *block, SDL_Renderer *renderer)
{
    if (!(block->isDestroyed))
    {
        block->rect.x = block->position.x;
        block->rect.y = block->position.y;
    }
    else
    {
        block->rect.x = block->position.x = -100;
        block->rect.y = block->position.y = -100;
    }

    SDL_RenderCopy(renderer, block->texture, NULL, &block->rect);
}

void DestroyBlock(Block *block)
{
    SDL_DestroyTexture(block->texture);
    free(block);
}

void DrawBlocks(Block **blocks, int n, SDL_Renderer *renderer)
{
    for (int i = 0; i < n; i++)
        DrawBlock(blocks[i], renderer);
}

void DestroyBlocks(Block **blocks, int n)
{
    for (int i = 0; i < n; i++)
        DestroyBlock(blocks[i]);

    free(blocks);
}

void RestartBlocks(Block **blocks, int n)
{
    int x = 0;
    int y = 4;
    int offset = 10;
    for (int i = 0; i < n; i++)
    {
        if (i % 10 == 0 && i != 0)
        {
            y++;
        }

        if (x == 10)
        {
            x = 0;
        }

        blocks[i]->position.x = x * (blocks[i]->size.x + offset);
        blocks[i]->position.y = y * (blocks[i]->size.y + offset);
        blocks[i]->isDestroyed = false;
        x++;
    }
}

bool CheckWin(Block **blocks, int n)
{
    for (int i = 0; i < n; i++)
        if (!blocks[i]->isDestroyed)
        {
            return false;
        }

    return true;
}