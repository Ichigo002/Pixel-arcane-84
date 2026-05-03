#include <Arduino.h>
#include "TextRenderer.h"
#include "InputHandler.h"
#include "ActionHandler.h"

TextRenderer renderer;
InputHandler input;

ActionHandler action_handler(&renderer, &input);

char option = 0;
bool option_is_chosen = false;
bool btn_pressed = true;

void updateMenu()
{
    if (option_is_chosen)
        return;

    if (input.left())
    {
        option--;
        btn_pressed = true;
        if (option < 0)
            option = 4;
    }

    if (input.right())
    {
        option++;
        btn_pressed = true;
        if (option > 4)
            option = 0;
    }

    if (input.up())
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
        renderer.renderAnimatedText("1BROWSE CHARS", 13, true, 100);
        break;
    case 1:
        renderer.renderAnimatedText("2EXAMPLE ANIMATION", 18, true);
        break;
    case 2:
        renderer.renderAnimatedText("3CUSTOM ANIMATION", 17, true);
        break;
    case 3:
        renderer.renderAnimatedText("4TETRIS", 7, true);
        break;
    case 4:
        renderer.renderAnimatedText("5SNAKE", 6, true);
        break;
    default:
        renderer.renderAnimatedText("ERROR MENU", 10, true);
        break;
    }
}

void setup()
{
    renderer.begin();
    input.begin();
}

void loop()
{
    input.update();

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

        if (input.downLong()) // EXIT
        {
            action_handler.resetStates();
            option_is_chosen = false;
        }
    }

    renderer.update();
}
