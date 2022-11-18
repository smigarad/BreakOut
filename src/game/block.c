#include "../../header/Game/block.h"

void DrawBlock(Block* block, SDL_Renderer* renderer)
{
    if(!(block->isDestroyed))
    {
        block->rect.x = block->position.x;
        block->rect.y = block->position.y;
    }
    else
    {
        block->rect.x = block->position.x  = -100;
        block->rect.y = block->position.y = -100;
    }
    
    SDL_RenderCopy(renderer, block->texture, NULL, &block->rect);
}

void DestroyBlock(Block* block)
{
    SDL_DestroyTexture(block->texture);
    free(block);
}

char* ChooseTexture()
{
    time_t t;
    srand((unsigned) time(&t));

    int random = rand() %7;
    char* fileName;
    if(random ==0)
        fileName = "assets/Blocks/blue.png";

    if(random ==1)
        fileName = "assets/Blocks/dblue.png";

    if(random ==2)
        fileName = "assets/Blocks/green.png";

    if(random ==3)
        fileName = "assets/Blocks/orange.png";

    if(random ==4)
        fileName = "assets/Blocks/purple.png";

    if(random ==5)
        fileName = "assets/Blocks/red.png";

    if(random ==6)
        fileName = "assets/Blocks/yellow.png";
    
    return fileName;
}

void DrawBlocks(Block** blocks, int n, SDL_Renderer* renderer)
{
    for(int i =0; i <n; i++)
    {
        DrawBlock(blocks[i], renderer);
    }
}


void DestroyBlocks(Block** blocks, int n)
{
    for(int i =0; i <n; i++)
    {
        DestroyBlock(blocks[i]);
    }
    free(blocks);
}

void RestartBlocks(Block** blocks, int n)
{
    int x=0;
    int y=4;
    for(int i =0; i < n; i++)
    {
        if (i % 10 == 0 && i != 0)
        {
            y++;
        }
        if(x == 10)
        {
            x = 0;
        }

        blocks[i]->position = (Vec2){x * blocks[i]->size.x,blocks[i]->size.y * y};
        blocks[i]->isDestroyed = false;
        x++;
        
    }
}

bool CheckWin(Block** blocks, int n)
{
    for(int i =0; i < n; i++)
    {
        if(!blocks[i]->isDestroyed)
        {
            return false;
        }
    }
    return true;
}