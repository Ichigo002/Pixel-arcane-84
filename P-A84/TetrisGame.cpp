#include "TetrisGame.h"

// Definicje klocków 3x3 w pamięci Flash (9 bitów na kształt)
const uint16_t tetrominoes[] PROGMEM = {
    0b001001011, // L: o..|o..|oo.
    0b010111000, // T: .o.|ooo|...
    0b000110110, // Kwadrat: ...|oo.|oo. (2x2 wewnątrz 3x3)
    0b010010010, // Linia: .o.|.o.|.o. (1x3)
    0b011110000  // Z: .oo|oo.|...
};

TetrisGame::TetrisGame(TextRenderer* render, InputHandler* input) {
    this->render = render;
    this->input = input;
    resetState();
}

void TetrisGame::resetState() {
    for(uint8_t i=0; i<8; i++) board[i] = 0;
    isGameOver = false;
    last_fall = millis();
    spawnPiece();
}

void TetrisGame::updatePieceMask() {
    uint16_t base = pgm_read_word(&tetrominoes[piece_id]);
    current_piece = 0;

    for (uint8_t i = 0; i < 3; i++) {
        for (uint8_t j = 0; j < 3; j++) {
            // Wyciągamy bit z siatki 3x3
            bool bit = (base >> (i * 3 + j)) & 1;
            if (bit) {
                int8_t ni, nj;
                // Rotacja siatki 3x3
                if (rotation == 0)      { ni = i; nj = j; }
                else if (rotation == 1) { ni = j; nj = 2 - i; }
                else if (rotation == 2) { ni = 2 - i; nj = 2 - j; }
                else                    { ni = 2 - j; nj = i; }
                
                // Kluczowe: Mapowanie na siatkę 4x4 (wiersz * 4 + kolumna)
                // To zapobiega "dziurom" w klocku
                current_piece |= (1 << (ni * 4 + nj));
            }
        }
    }
}

void TetrisGame::spawnPiece() {
    px = 3; py = 0;
    piece_id = random(0, 5);
    rotation = 0;
    updatePieceMask();
    if(checkCollision(px, py, current_piece)) isGameOver = true;
}

bool TetrisGame::checkCollision(int8_t nx, int8_t ny, uint16_t mask) {
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            if ((mask >> (i * 4 + j)) & 1) {
                int8_t bx = nx + j;
                int8_t by = ny + i;
                if (bx < 0 || bx >= 8 || by >= 8) return true;
                if (by >= 0 && (board[by] & (1 << bx))) return true;
            }
        }
    }
    return false;
}

void TetrisGame::lockPiece() {
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            if ((current_piece >> (i * 4 + j)) & 1) {
                if (py + i >= 0 && py + i < 8) board[py + i] |= (1 << (px + j));
            }
        }
    }
}

void TetrisGame::clearLines() {
    for (int8_t i = 7; i >= 0; i--) {
        if (board[i] == 0xFF) {
            for (int8_t j = i; j > 0; j--) board[j] = board[j-1];
            board[0] = 0;
            i++; // Sprawdź ten sam poziom ponownie
        }
    }
}

void TetrisGame::update() {
    if (isGameOver) return;

    bool changed = false;

    if (input->up()) { // OBROT
        uint8_t old_rot = rotation;
        rotation = (rotation + 1) % 4;
        updatePieceMask();
        if (checkCollision(px, py, current_piece)) {
            rotation = old_rot;
            updatePieceMask();
        }
        changed = true;
    }

    if (input->right() && !checkCollision(px - 1, py, current_piece)) { px--; changed = true; }
    if (input->left() && !checkCollision(px + 1, py, current_piece)) { px++; changed = true; }
    if (input->down() && !checkCollision(px, py + 1, current_piece)) { py++; changed = true; }

    if (millis() - last_fall > 600) {
        if (!checkCollision(px, py + 1, current_piece)) {
            py++;
        } else {
            lockPiece();
            clearLines();
            spawnPiece();
        }
        last_fall = millis();
        changed = true;
    }

    if (changed) draw();
}

void TetrisGame::draw() {
    Glyph g;
    for (uint8_t i = 0; i < 8; i++) g.raw_ascii[i] = board[i];
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            if ((current_piece >> (i * 4 + j)) & 1) {
                int8_t by = py + i;
                if (by >= 0 && by < 8) g.raw_ascii[by] |= (1 << (px + j));
            }
        }
    }
    render->renderGlyph(g);
}

bool TetrisGame::IsGameFinished() {
    if (isGameOver) {
        return true;
    }
    return false;
}
