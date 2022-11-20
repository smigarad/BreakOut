#include "../../header/Game/ball.h"

void DrawBall(Ball *ball, SDL_Renderer *renderer)
{
    ball->rect.x = ball->position.x;
    ball->rect.y = ball->position.y;
    SDL_RenderCopy(renderer, ball->texture, NULL, &ball->rect);
}

void UpdateBall(Ball *ball, Player *player, Application *app)
{
    if (!player->controls[START] || player->controls[RESTART])
        SetBall(ball, player);

    ball->position.x += ball->velocity.x * ball->speed;
    ball->position.y += ball->velocity.y * ball->speed;
    WallBounce(ball, app);
    BallColissionWithPlayer(ball, player);
}

void SetBall(Ball *ball, Player *player)
{
    ball->position.x = player->position.x + player->size.x / 2 - ball->size.x / 2;
    ball->position.y = player->position.y - ball->size.y;
}

void WallBounce(Ball *ball, Application *app)
{
    if (ball->position.x <= 0 || ball->position.x >= app->size.x - ball->size.x) // odraz od bočních stěn
        ball->velocity.x *= -1;                                                  // obrátí směr pohybu po ose x

    if (ball->position.y <= 0 || ball->position.y >= app->size.y - ball->size.y) // odraz od horní a dolní stěny
        ball->velocity.y *= -1;                                                  // obrátí směr pohybu po ose y
}

void BallColissionWithPlayer(Ball *ball, Player *player)
{
    if (ball->position.x + ball->size.x >= player->position.x && ball->position.x <= player->position.x + player->size.x) // zdali je míček v rozsahu hráče na ose x
    {
        if (ball->position.y + ball->size.y >= player->position.y && ball->position.y <= player->position.y + player->size.y) // zdali je míček v rozsahu hráče na ose y
        {
            ball->velocity.y *= -1;                                                            // Změna směru pohybu míčku po ose y
            if (ball->position.x + ball->size.x / 2 < player->position.x + player->size.x / 2) // player->size.x/2 = polovina hráče
                ball->velocity.x = -1;                                                         // musí jít vždy do leva
            else
                ball->velocity.x = 1; // musí jít vždy doprava
        }
    }

    if (ball->position.y + ball->size.y > player->position.y + player->size.y / 2) // míček je pod hráčem
    {
        player->health--;
        player->controls[START] = false;
        player->score = player->score > 20 ? player->score - 20 : 0;
    }
}

void BallCollisionWithBlock(Ball *ball, Block *block, Player *player) // Na nic lepšího jsem nedokázal přijít
{
    bool collision = SDL_HasIntersection(&ball->rect, &block->rect); // Zda li nastala kolize
    int ballCenterX = ball->position.x + ball->size.x / 2;           // Střed míčku na ose x
    int ballCenterY = ball->position.y + ball->size.y / 2;           // Střed míčku na ose y
    int blockCenterX = block->position.x + block->size.x / 2;        // Střed bloku na ose x
    int blockCenterY = block->position.y + block->size.y / 2;        // Střed bloku na ose y
    if (collision)
    {
        if(ballCenterX > block->position.x + block->size.x)
        {
            ball->velocity.x *= -1;
        }
        else if(ballCenterX < block->position.x)
        {
            ball->velocity.x *= -1;
        }
        else if(ballCenterY > block->position.y + block->size.y)
        {
            ball->velocity.y *= -1;
        }
        else if(ballCenterY < block->position.y)
        {
            ball->velocity.y *= -1;
        }        
        block->isDestroyed = true;
        player->score += 10;
    }
}

void BlocksCollision(int n, Ball *ball, Block **blocks, Player *player)
{
    for (int i = 0; i < n; i++)
        BallCollisionWithBlock(ball, blocks[i], player);
}

void DestroyBall(Ball *ball)
{
    SDL_DestroyTexture(ball->texture);
    free(ball);
    return;
}