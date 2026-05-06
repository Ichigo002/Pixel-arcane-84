#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <Arduino.h>
#include "TextRenderer.h"
#include "InputHandler.h"

class SnakeGame {
public:
    SnakeGame(TextRenderer* render, InputHandler* input);
    void update();
    void resetState();
    bool IsGameFinished();

private:
    void gameOver();
    void getRandomApple();
    void renderSnakeAndApple();
    
    // Pakowanie bitowe: 64 segmenty * 2 bity = 128 bitów = 16 bajtów
    // 00=Góra, 01=Dół, 10=Lewo, 11=Prawo
    uint8_t snake_chain[16]; 
    
    void setDir(uint8_t index, uint8_t dir);
    uint8_t getDir(uint8_t index);

    TextRenderer* render;
    InputHandler *input;

    uint32_t refresh_timestamp;
    uint16_t refresh_snake_time_ms;

    int8_t move_x, move_y;
    bool isGameOver;

    uint8_t snake_tail_idx; // Indeks w tablicy kołowej
    uint8_t snake_head_idx;
    uint8_t head_x, head_y;
    uint8_t tail_x, tail_y;

    uint8_t apple_x, apple_y;
    uint8_t record;
};

#endif
