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
    bool current_state = (digitalRead(btn_pin) == LOW);

    if(current_state && !last_button_state && cooldown_timer.hasExpired(200))
    {
        last_button_state = true;
        cooldown_timer.resetHasExpired();
        return true;
    }

    if(!current_state) {
        last_button_state = false;
    }

    return false;
}

bool InputHandler::isButtonPressedFor2Sec(uint8_t btn_pin)
{
    if(digitalRead(btn_pin) == LOW && !exit_btn_pressed)
    {
        exit_btn_pressed = true;
        exit_btn_timer.resetHasExpired();
    }

    if(exit_btn_timer.hasExpired(2000) && exit_btn_pressed)
    {
        return true;
    }

    if(digitalRead(btn_pin) == HIGH)
    {
        exit_btn_pressed = false;
    } 
    return false;
}
