#include "ActionHandler.h"

ActionHandler::ActionHandler(TextRenderer *render, InputHandler *input)
{
    this->render = render;
    this->input = input;

    resetStates();
}

ActionHandler::~ActionHandler()
{
}

void ActionHandler::runBrowseChars()
{
    if (input->isButtonPressed(BTN_LEFT))
    {
        current_browse_chars_ascii--;
        refresh_render_cooldown = false;

        if (current_browse_chars_ascii < 1)
            current_browse_chars_ascii = ascii_size_table-1;
    }
    if (input->isButtonPressed(BTN_RIGHT))
    {
        current_browse_chars_ascii++;
        refresh_render_cooldown = false;

        if (current_browse_chars_ascii >= ascii_size_table)
            current_browse_chars_ascii = 1;
    }

    if (refresh_render_cooldown)
        return;

    refresh_render_cooldown = true;
    Glyph g = _readASCII(current_browse_chars_ascii);
    render->renderGlyph(g);
}

void ActionHandler::runExampleAnimation()
{
    if (input->isButtonPressed(BTN_LEFT))
    {
        render->changeAnimationSpeed(render->getAnimationSpeed() + 15);
    }
    if (input->isButtonPressed(BTN_RIGHT))
    {
        render->changeAnimationSpeed(render->getAnimationSpeed() - 15);
    }

    if (input->isButtonPressed(BTN_UP))
    {
        render->increaseBrightness();
    }
    if (input->isButtonPressed(BTN_DOWN))
    {
        render->decreaseBrightness();
    }

    if (refresh_render_cooldown)
        return;

    refresh_render_cooldown = true;
    render->renderAnimatedText("DIE WITH MEMORIES, NOT DREAMS.   TO BE INTERESTING - BE INTERESTED", 66, true);
}

void ActionHandler::runCustomAnimation()
{
    render->renderASCII('C');
}

void ActionHandler::resetStates()
{
    refresh_render_cooldown = false;
    current_browse_chars_ascii = 1;
}
