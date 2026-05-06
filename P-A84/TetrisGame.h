#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "TextRenderer.h"
#include "InputHandler.h"

//CHALLANGE: make tetris with only:
// 514 bytes free flash
// 66  bytes free memory
// Challange accepted!

class TetrisGame
{

public:
    TetrisGame(TextRenderer *render, InputHandler *input);
    ~TetrisGame();

    void update();

    void resetState();

    bool IsGameFinished();

private:
    void gameOver();

    Glyph g;
    uint32_t refresh_timestamp;
    short int refresh_tetris_fall_time_ms;

    TextRenderer *render;
    InputHandler *input;

    bool isGameOver;
    int score;
};

#endif