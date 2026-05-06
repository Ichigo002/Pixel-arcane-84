#include "SnakeGame.h"

SnakeGame::SnakeGame(TextRenderer *render, InputHandler *input)
{
    this->render = render;
    this->input = input;

    resetState();

    refresh_timestamp = millis();
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::update()
{
    if(isGameOver)
        return;

    if (input->down() && move_y != 1)
    {
        move_x = 0;
        move_y = -1;
    }
    if (input->up() && move_y != -1)
    {
        move_x = 0;
        move_y = 1;
    }
    if (input->left() && move_x != 1)
    {
        move_x = -1;
        move_y = 0;
    }
    if (input->right() && move_x != -1)
    {
        move_x = 1;
        move_y = 0;
    }

    if (millis() - refresh_timestamp >= refresh_snake_time_ms)
    {
        refresh_timestamp = millis();

        moveSnakeChainBy(move_x, move_y);
    }

    char x, y;
    translateSnakeChainToXY(x, y, snake_chain[snake_head]);

    if (x == apple_x && y == apple_y)
    {
        snakeGettingFat(x, y);
        getRandomApple();
        record++;
    }
    if(!isGameOver)
        renderSnakeAndApple();
}

void SnakeGame::resetState()
{
    refresh_snake_time_ms = 260;
    
    move_x = 0;
    move_y = 1;

    snake_chain[0] = translateXYToSnakeChain(4, 4);
    snake_chain[1] = translateXYToSnakeChain(4, 5);

    for (char i = 2; i < 64; i++)
    {
        snake_chain[i] = 0;
    }

    snake_tail = 0;
    snake_head = 1;

    record = 0;
    isGameOver = false;

    getRandomApple();
}

bool SnakeGame::IsGameFinished()
{
    return isGameOver && render->isAnimationDone();
}

void SnakeGame::gameOver()
{
    sprintf(gameOverTxt, "GAME OVER ( SCORE %d", record);

    if(record < 10)
        gameOverTxt[19] = ' ';

    render->renderAnimatedText(gameOverTxt, 20);
    
    isGameOver = true;
}

void SnakeGame::getRandomApple()
{
    apple_x = random(1, 9); // random: 1-8
    apple_y = random(1, 9); // random: 1-8
}

void SnakeGame::renderSnakeAndApple()
{
    
    for (uint8_t i = 0; i < 8; i++)
    {
        g.raw_ascii[i] = 0;
    }

    for (size_t i = 0; i < 64; i++)
    {
        char x, y;
        translateSnakeChainToXY(x, y, snake_chain[i]);
        if (x != 0 && y != 0)
        {
            g.raw_ascii[y - 1] = g.raw_ascii[y - 1] | (1 << (x - 1));
        }
    }

    // APPLE RENDERING
    g.raw_ascii[apple_y - 1] = g.raw_ascii[apple_y - 1] | (1 << (apple_x - 1));

    render->renderGlyph(g);
}

void SnakeGame::snakeGettingFat(char x, char y)
{
    snake_head++;
    if(snake_head >= 64)
        snake_head = 0;

    snake_chain[snake_head] = translateXYToSnakeChain(x, y);
}

void SnakeGame::moveSnakeChainBy(char x, char y)
{
    snake_chain[snake_tail] = 0;
    snake_tail++;
    if(snake_tail >= 64)
        snake_tail = 0;

    char hx, hy;
    translateSnakeChainToXY(hx, hy, snake_chain[snake_head]);
    hx -= x;
    hy -= y;

    if (hx > 8 || hx < 1 || hy > 8 || hy < 1)
        gameOver();

    snake_head++;
    if(snake_head >= 64)
        snake_head = 0;

    if((g.raw_ascii[hy-1] >> (hx-1)) & 1 == 1 && hx != apple_x && hy != apple_y)
        gameOver();

    snake_chain[snake_head] = translateXYToSnakeChain(hx, hy);

}

uint8_t SnakeGame::translateXYToSnakeChain(char x, char y)
{
    return (x << 4) | y;
}

void SnakeGame::translateSnakeChainToXY(char &x, char &y, uint8_t v)
{
    y = v & 15;         // 15 => 0000 1111
    x = (v & 240) >> 4; // 240 => 1111 0000
}
