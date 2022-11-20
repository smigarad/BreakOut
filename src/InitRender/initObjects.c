#include "../../header/initObjects.h"

Application *ApplicationConstructor()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Application *application = malloc(sizeof(Application));
    application->window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    application->renderer = SDL_CreateRenderer(application->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    application->running = true;
    application->size = (Vec2){WINDOW_WIDTH, WINDOW_HEIGHT};
    return application;
}

Player *PlayerConstructor(SDL_Renderer *renderer)
{
    Player *player = malloc(sizeof(Player));
    player->size = (Vec2){PLAYER_WIDTH, PLAYER_HEIGHT};
    player->position = (Vec2){WINDOW_WIDTH / 2 - player->size.x / 2, WINDOW_HEIGHT - 50};
    player->speed = DEFAULT_SPEED;
    player->velocity = (Vec2){5, 5};
    player->rect = (SDL_Rect){player->position.x, player->position.y, player->size.x, player->size.y};
    for (int i = 0; i < 6; i++)
    {
        player->controls[i] = false;
    }
    player->score = 0;
    player->health = 3;
    player->start = false;
    SDL_Surface *surface = IMG_Load("assets/player.png");
    player->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return player;
}

Ball *BallConstructor(SDL_Renderer *renderer)
{
    Ball *ball = malloc(sizeof(Ball));
    ball->position = (Vec2){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    ball->size = (Vec2){BALL_WIDTH, BALL_WIDTH};
    ball->speed = BALL_SPEED;
    ball->rect = (SDL_Rect){ball->position.x, ball->position.y, ball->size.x, ball->size.y};
    ball->velocity = (Vec2){1, 1};
    ball->start = false;
    ball->radius = ball->size.x / 2;
    SDL_Surface *surface = IMG_Load("assets/ball.png");
    ball->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return ball;
}

Background *BackgroundConstructor(SDL_Renderer *renderer)
{
    Background *background = malloc(sizeof(Background));
    background->position = (Vec2){-60, -50};
    background->size = (Vec2){BACKGROUND_WIDTH, BACKGROUND_HEIGHT};
    background->rect = (SDL_Rect){background->position.x, background->position.y, background->size.x, background->size.y};
    SDL_Surface *surface = IMG_Load("assets/background.png");
    background->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return background;
}

Font *FontConstructor()
{
    Font *font = malloc(sizeof(Font));
    font->font = TTF_OpenFont("assets/Fonts/RetroGaming.ttf", 20);
    font->color = (SDL_Color){255, 255, 255, 255}; // bilá
    font->position = (Vec2){10, 10};
    font->size = (Vec2){30, 30};
    font->rect = (SDL_Rect){font->position.x, font->position.y, font->size.x, font->size.y};
    font->texture = NULL;
    return font;
}

Block *BlockConstructor(SDL_Renderer *renderer)
{
    Block *block = malloc(sizeof(Block));
    block->size = (Vec2){BLOCK_WIDTH, BLOCK_HEIGHT};
    block->rect.w = block->size.x;
    block->rect.h = block->size.y;
    block->isDestroyed = false;
    return block;
}

SDL_Texture **SetTextures(SDL_Renderer *renderer)
{
    SDL_Texture **textures = malloc(sizeof(SDL_Texture *) * 7);
    SDL_Surface *surface = IMG_Load("assets/Blocks/blue.png");
    textures[0] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("assets/Blocks/dblue.png");
    textures[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("assets//Blocks/green.png");
    textures[2] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("assets/Blocks/orange.png");
    textures[3] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("assets/Blocks/purple.png");
    textures[4] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("assets/Blocks/red.png");
    textures[5] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("assets/Blocks/yellow.png");
    textures[6] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return textures;
}
Block **BlocksConstructor(int n, SDL_Renderer *renderer, SDL_Texture **textures)
{
    srand(time(NULL));
    Block **blocks = malloc(n * sizeof(Block *));
    int x = 0;
    int y = 4;
    int offset = 10;
    for (int i = 0; i < n; i++)
    {
        if (i % 10 == 0 && i != 0)
            y++;
        if (x == 10)
            x = 0;

        blocks[i] = BlockConstructor(renderer);
        blocks[i]->texture = textures[rand() % 7];
        blocks[i]->position.x = x * (blocks[i]->size.x + offset);
        blocks[i]->position.y = y * (blocks[i]->size.y + offset);

        x++;
    }
    return blocks;
}
