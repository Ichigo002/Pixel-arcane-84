#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <Arduino.h>
#include "TextRenderer.h"
#include "InputHandler.h"

class TetrisGame {
public:
    TetrisGame(TextRenderer* render, InputHandler* input);
    void update();
    void resetState();
    bool IsGameFinished();

private:
    void spawnPiece();
    void draw();
    bool checkCollision(int8_t nx, int8_t ny, uint16_t mask);
    void lockPiece();
    void clearLines();
    void updatePieceMask();

    TextRenderer* render;
    InputHandler* input;

    uint8_t board[8];      // Plansza 8x8
    uint16_t current_piece; // Maska bitowa 4x4 aktualnego klocka
    int8_t px, py;         // Pozycja klocka
    uint8_t piece_id;      // Typ klocka
    uint8_t rotation;      // Stan obrotu (0-3)
    
    uint32_t last_fall;
    bool isGameOver;
};

#endif
