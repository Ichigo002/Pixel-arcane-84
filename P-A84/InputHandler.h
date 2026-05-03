#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "pins.h"
#include <TimerKernel.h>

#define BTN_UP btnRightPin
#define BTN_DOWN btnDownPin
#define BTN_RIGHT btnUpPin
#define BTN_LEFT btnLeftPin

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    bool isButtonPressed(uint8_t btn_pin);

    bool isButtonPressedFor2Sec(uint8_t btn_pin);
private:
    TimerKernel exit_btn_timer;
    TimerKernel cooldown_timer;
    bool last_button_state;
    bool exit_btn_pressed;
};




#endif