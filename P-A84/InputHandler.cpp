#include "InputHandler.h"

InputHandler::InputHandler(/* args */)
{
    exit_btn_pressed = false;
}

InputHandler::~InputHandler()
{
}

bool InputHandler::isButtonPressed(uint8_t btn_pin)
{
    return digitalRead(btn_pin) == LOW;
}

bool InputHandler::isExitButtonPressed()
{
    if (isButtonPressed(BTN_DOWN))
    {
        exit_btn_pressed = true;
        exit_btn_timer.resetHasExpired();
    }

    if (!exit_btn_pressed)
        return false;

    if (!exit_btn_timer.hasExpired(3000))
        return false;

    exit_btn_pressed = false;
    return true;
}
