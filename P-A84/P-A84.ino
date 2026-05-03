#include <Arduino.h>
#include "TextRenderer.h"
#include "InputHandler.h"
#include "ActionHandler.h"

TextRenderer renderer;
InputHandler input;

ActionHandler action_handler(&renderer, &input);

void setupPins()
{
    pinMode(rowDataPin, OUTPUT);
    pinMode(rowClockPin, OUTPUT);
    pinMode(rowLatchPin, OUTPUT);

    pinMode(colDataPin, OUTPUT);
    pinMode(colClockPin, OUTPUT);
    pinMode(colLatchPin, OUTPUT);

    pinMode(btnLeftPin, INPUT);
    pinMode(btnUpPin, INPUT);
    pinMode(btnDownPin, INPUT);
    pinMode(btnRightPin, INPUT);
}

char option = 0;
bool option_is_chosen = false;
bool btn_pressed = true;

void updateMenu()
{
    if (option_is_chosen)
        return;

    if (input.isButtonPressed(BTN_LEFT))
    {
        option--;
        btn_pressed = true;
        if (option < 0)
            option = 4;
    }

    if (input.isButtonPressed(BTN_RIGHT))
    {
        option++;
        btn_pressed = true;
        if (option > 4)
            option = 0;
    }

    if (input.isButtonPressed(BTN_UP))
    {
        btn_pressed = true;
        option_is_chosen = true;
        return;
    }

    if (!btn_pressed)
        return;

    btn_pressed = false;

    switch (option)
    {
    case 0:
        renderer.renderAnimatedText("P1BROWSE CHARS", 14, true);
        break;
    case 1:
        renderer.renderAnimatedText("P2EXAMPLE ANIMATION", 19, true);
        break;
    case 2:
        renderer.renderAnimatedText("P3CUSTOM ANIMATION", 18, true);
        break;
    case 3:
        renderer.renderAnimatedText("P4TETRIS", 8, true);
        break;
    case 4:
        renderer.renderAnimatedText("P4SNAKE", 7, true);
        break;
    default:
        renderer.renderAnimatedText("ERROR MENU", 10, true);
        break;
    }
}

void setup()
{
    setupPins();
}

void loop()
{
    updateMenu();

    if (option_is_chosen)
    {
        switch (option)
        {
        case 0: // browse chars
            action_handler.runBrowseChars();
            break;
        case 1: // example animation
            action_handler.runExampleAnimation();
            break;
        case 2: // custom animations
            action_handler.runCustomAnimation();
            break;
        case 3: // tetris

            break;
        case 4: // snake

            break;
        }

        if (input.isButtonPressedFor2Sec(BTN_DOWN)) // EXIT
        {
            action_handler.resetStates();
            option_is_chosen = false;
        }
    }

    renderer.update();
}
