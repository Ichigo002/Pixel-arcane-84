#include "SnakeGame.h"

SnakeGame::SnakeGame(TextRenderer *render, InputHandler *input) {
    this->render = render;
    this->input = input;
    resetState();
}

void SnakeGame::setDir(uint8_t index, uint8_t dir) {
    uint8_t byteIdx = index / 4;
    uint8_t bitPos = (index % 4) * 2;
    snake_chain[byteIdx] &= ~(0x03 << bitPos); 
    snake_chain[byteIdx] |= (dir << bitPos);
}

uint8_t SnakeGame::getDir(uint8_t index) {
    return (snake_chain[index / 4] >> ((index % 4) * 2)) & 0x03;
}

void SnakeGame::resetState() {
    refresh_snake_time_ms = 260;
    move_x = 0; move_y = -1;
    isGameOver = false;
    record = 0;

    head_x = 4; head_y = 5;
    tail_x = 4; tail_y = 4;
    
    snake_tail_idx = 0;
    snake_head_idx = 1;

    // Inicjalizacja kierunku (wąż startuje pionowo)
    // 00=Góra, 01=Dół, 10=Lewo, 11=Prawo
    setDir(0, 0); // Ogon patrzy w górę do głowy

    for(uint8_t i=0; i<16; i++) snake_chain[i] = 0;
    setDir(0, 0); 

    refresh_timestamp = millis();
    getRandomApple();
}

void SnakeGame::update() {
    if (isGameOver) return;

    // Sterowanie
    if (input->up() && move_y != 1)  { move_x = 0; move_y = -1; }
    if (input->down() && move_y != -1)    { move_x = 0; move_y = 1; }
    if (input->right() && move_x != 1)  { move_x = -1; move_y = 0; }
    if (input->left() && move_x != -1) { move_x = 1; move_y = 0; }

    if (millis() - refresh_timestamp >= refresh_snake_time_ms) {
        refresh_timestamp = millis();
        
        // Logika ruchu
        uint8_t next_x = head_x + move_x;
        uint8_t next_y = head_y + move_y;

        // Kolizja ze ścianami
        if (next_x > 8 || next_x < 1 || next_y > 8 || next_y < 1) {
            gameOver();
            return;
        }

        // Zapamiętaj kierunek ruchu w starym head_idx
        uint8_t d = 0; // 0:G, 1:D, 2:L, 3:P
        if (move_y == 1) d = 0; else if (move_y == -1) d = 1;
        else if (move_x == -1) d = 2; else if (move_x == 1) d = 3;
        setDir(snake_head_idx, d);

        head_x = next_x;
        head_y = next_y;
        snake_head_idx = (snake_head_idx + 1) % 64;

        if (head_x == apple_x && head_y == apple_y) {
            record++;
            getRandomApple();
            // Nie przesuwamy ogona = wąż rośnie
        } else {
            // Przesuwamy ogon na podstawie zapisanego kierunku
            uint8_t td = getDir(snake_tail_idx);
            if (td == 0) tail_y++; else if (td == 1) tail_y--;
            else if (td == 2) tail_x--; else if (td == 3) tail_x++;
            snake_tail_idx = (snake_tail_idx + 1) % 64;
        }
        
        renderSnakeAndApple();
    }
}

void SnakeGame::renderSnakeAndApple() {
    Glyph g; 
    for (uint8_t i = 0; i < 8; i++) g.raw_ascii[i] = 0;

    uint8_t tx = tail_x, ty = tail_y;
    uint8_t curr = snake_tail_idx;
    
    while (curr != snake_head_idx) {
        // Rysujemy segment
        if (tx >= 1 && tx <= 8 && ty >= 1 && ty <= 8) {
            g.raw_ascii[ty - 1] |= (1 << (tx - 1));
        }
        
        // --- TUTAJ DODAJEMY SPRAWDZANIE KOLIZJI ---
        // Jeśli aktualnie rysowany segment (tx, ty) ma te same 
        // współrzędne co nowa głowa (head_x, head_y) -> Kolizja!
        if (tx == head_x && ty == head_y) {
            gameOver();
            return; // Przerywamy rysowanie, bo gra się skończyła
        }
        // ------------------------------------------

        uint8_t d = getDir(curr);
        if (d == 0) ty++; else if (d == 1) ty--;
        else if (d == 2) tx--; else if (d == 3) tx++;
        curr = (curr + 1) % 64;
    }
    
    // Na końcu rysujemy głowę i jabłko
    g.raw_ascii[head_y - 1] |= (1 << (head_x - 1));
    g.raw_ascii[apple_y - 1] |= (1 << (apple_x - 1));

    render->renderGlyph(g);
}

void SnakeGame::gameOver() {
    isGameOver = true;
    
    char buffer[17]; 
    
    // Kopiujemy "GAME OVER (" z Flash do RAMu na chwilę
    strcpy_P(buffer, (PGM_P)F("GAME OVER ( ")); 
    
    // Dopisujemy liczbę na końcu
    char numBuf[4];
    itoa(record, numBuf, 10);
    strcat(buffer, numBuf);
    
    render->renderAnimatedText(buffer, strlen(buffer));
}

void SnakeGame::getRandomApple() {
    apple_x = random(1, 9);
    apple_y = random(1, 9);
}

bool SnakeGame::IsGameFinished() {
    return isGameOver && render->isAnimationDone();
}
