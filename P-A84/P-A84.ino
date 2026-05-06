#include <Arduino.h>
#include "TextRenderer.h"
#include "InputHandler.h"
#include "ActionHandler.h"
#include "SnakeGame.h"
#include "TetrisGame.h"

TextRenderer renderer;
InputHandler input;


TetrisGame tetris(&renderer, &input);
SnakeGame snake(&renderer, &input);
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
    case 2:
        renderer.renderAnimatedText("3BROWSE CHARS", 13, true, 100);
        break;
    case 3:
        renderer.renderAnimatedText("4EXAMPLE ANIM", 13, true);
        break;
    case 4:
        renderer.renderAnimatedText("5CUSTOM ANIM", 12, true);
        break;
    case 0:
        renderer.renderAnimatedText("1TETRIS", 7, true);
        break;
    case 1:
        renderer.renderAnimatedText("2SNAKE", 6, true);
        break;
    default:
        break;
    }
}

void setup()
{
    renderer.begin();
    input.begin();
    //renderer.renderAnimatedText("LORENZ - KLIMATYZACJA I OGRZEWANIE", 34, true);
}

void loop()
{
    //renderer.update();
    //return;
    input.update();

    updateMenu();

    if (option_is_chosen)
    {
        switch (option)
        {
        case 2: // browse chars
            action_handler.runBrowseChars();
            break;
        case 3: // example animation
            action_handler.runExampleAnimation();
            break;
        case 4: // custom animations
            action_handler.runCustomAnimation();
            break;
        case 0: // tetris
            tetris.update();
            break;
        case 1: // snake
            snake.update();
            break;
        }

        if (input.downLong() || snake.IsGameFinished() || tetris.IsGameFinished()) // EXIT
        {
            action_handler.resetStates();
            snake.resetState();
            tetris.resetState();
            
            option_is_chosen = false;
        }
    }

    renderer.update();
}
