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
    return isButtonPressedFor2Sec(BTN_DOWN);
}

bool InputHandler::isButtonPressedFor2Sec(uint8_t btn_pin)
{
    if(isButtonPressed(btn_pin) && !exit_btn_pressed)
    {
        exit_btn_pressed = true;
        exit_btn_timer.resetHasExpired();
    }

    if(exit_btn_timer.hasExpired(2000) && exit_btn_pressed)
    {
        return true;
    }

    if(!isButtonPressed(btn_pin))
    {
        exit_btn_pressed = false;
    } 
    return false;
}
