#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../InitRender/application.h"
#include "../Game/player.h"
#include "../Game/block.h"

#define BALL_WIDTH 15
#define BALL_SPEED 3
typedef struct Ball{
    Vec2 position;
    Vec2 size;
    Vec2 velocity;
    u_short speed;
    SDL_Rect rect;
    SDL_Texture* texture;
    bool start;
} Ball;

void DrawBall(Ball* ball, SDL_Renderer* renderer);
void UpdateBall(Ball* ball,Player* player, Application* app);
void SetBall(Ball* ball,Player* player);
void WallBounce(Ball* ball, Application* app);
void BallColissionWithPlayer(Ball* ball, Player* player);
void DestroyBall(Ball* ball);
void BallCollisionWithBlock(Ball* ball, Block* block,Player* player);
void BlocksCollision(int n, Ball* ball, Block** blocks, Player* player);