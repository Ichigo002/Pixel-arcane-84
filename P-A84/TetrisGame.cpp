#include "TetrisGame.h"

TetrisGame::TetrisGame(TextRenderer *render, InputHandler *input)
{
    this->render = render;
    this->input = input;

    resetState();

    refresh_timestamp = millis();
}

TetrisGame::~TetrisGame()
{
}

void TetrisGame::update()
{
    if(isGameOver)
        return;

    if (input->down() )
    {
        
    }
    if (input->up())
    {
        
    }
    if (input->left())
    {
        
    }
    if (input->right())
    {
        
    }

    if (millis() - refresh_timestamp >= refresh_tetris_fall_time_ms)
    {
        refresh_timestamp = millis();

    }

   // if(!isGameOver)
        //renderSnakeAndApple();
}

void TetrisGame::resetState()
{
    refresh_tetris_fall_time_ms = 500;
    score = 0;
    isGameOver = false;
}

bool TetrisGame::IsGameFinished()
{
    return isGameOver;
}

void TetrisGame::gameOver()
{

}
