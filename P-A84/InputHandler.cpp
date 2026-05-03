#include "InputHandler.h"



#define HOLD_THRESHOLD 50

void InputHandler::begin()
{
    pinMode(btnUpPin, INPUT);
    pinMode(btnDownPin, INPUT);
    pinMode(btnLeftPin, INPUT);
    pinMode(btnRightPin, INPUT);
}

void InputHandler::update()
{
    last = state;
    state = 0;

    if (digitalRead(btnUpPin) == LOW)    state |= (1 << 0);
    if (digitalRead(btnDownPin) == LOW)  state |= (1 << 1);
    if (digitalRead(btnLeftPin) == LOW)  state |= (1 << 2);
    if (digitalRead(btnRightPin) == LOW) state |= (1 << 3);

    // debounce (tickowy)
    if (state != last) {
        debounce = 5;
    }

    if (debounce > 0) {
        debounce--;
        return;
    }

    // liczniki przytrzymania
    for (uint8_t i = 0; i < 4; i++) {
        if (state & (1 << i)) {
            if (hold[i] < 255) hold[i]++;
        } else {
            hold[i] = 0;
        }
    }
}

// ===== klik =====
bool InputHandler::up()    { return (state & (1<<0)) && !(last & (1<<0)); }
bool InputHandler::down()  { return (state & (1<<1)) && !(last & (1<<1)); }
bool InputHandler::left()  { return (state & (1<<2)) && !(last & (1<<2)); }
bool InputHandler::right() { return (state & (1<<3)) && !(last & (1<<3)); }

// ===== przytrzymanie =====
bool InputHandler::upLong()    { return hold[0] == HOLD_THRESHOLD; }
bool InputHandler::downLong()  { return hold[1] == HOLD_THRESHOLD; }
bool InputHandler::leftLong()  { return hold[2] == HOLD_THRESHOLD; }
bool InputHandler::rightLong() { return hold[3] == HOLD_THRESHOLD; }