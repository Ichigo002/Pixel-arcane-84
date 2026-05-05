#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "TextRenderer.h"
#include "InputHandler.h"

/*

BOARD (start position)
Y
8
7
6
5       S
4       S
3       
2
1
  1 2 3 4 5 6 7 8 X

uint8_t frame position of snake_chain

Pos:X     Y
0b 0000 0000

*/

class SnakeGame
{

public:
    SnakeGame(TextRenderer* render, InputHandler* input);
    ~SnakeGame();

    void update();

    void resetState();

    bool IsGameFinished();
private:

    void gameOver();

    void getRandomApple();

    void renderSnakeAndApple();

    void snakeGettingFat(char x, char y);

    // y: 1 = move up, 0 = no move, -1 = move down
    // x: 1 = move right, 0 = no move, -1 = move left
    void moveSnakeChainBy(char x = 0, char y = 0);
    
    uint8_t translateXYToSnakeChain(char x, char y);
    void translateSnakeChainToXY(char& x, char& y, uint8_t v);

    TextRenderer* render;
    InputHandler *input;

    uint32_t refresh_timestamp;
    short int refresh_snake_time_ms;

    char move_x, move_y;
    bool isGameOver;
    char gameOverTxt[20];

    char snake_tail;
    char snake_head;

    char snake_chain[64];

    char apple_x, apple_y;
    int record;
};


#endif