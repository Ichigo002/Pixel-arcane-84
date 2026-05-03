#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "pins.h"
#include <Arduino.h>

class InputHandler
{
public:
    void begin();
    void update();

    // klik (zbocze)
    bool up();
    bool down();
    bool left();
    bool right();

    // przytrzymanie ~2s
    bool upLong();
    bool downLong();
    bool leftLong();
    bool rightLong();

private:
    uint8_t state = 0;
    uint8_t last = 0;
    uint8_t debounce = 0;
    uint8_t hold[4] = {0};
};

#endif