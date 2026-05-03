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
    if (input->left())
    {
        current_browse_chars_ascii--;
        refresh_render_cooldown = false;

        if (current_browse_chars_ascii < 1)
            current_browse_chars_ascii = ascii_size_table - 1;
    }
    if (input->right())
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
    if (input->left())
        render->changeAnimationSpeed(render->getAnimationSpeed() + 15);

    if (input->right())
    {
        render->changeAnimationSpeed(render->getAnimationSpeed() - 15);
    }

    if (input->up())
    {
        render->increaseBrightness();
    }
    if (input->down())
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
    if (input->left())
    {
        current_browse_chars_ascii--;
        refresh_render_cooldown = false;

        if (current_browse_chars_ascii < 1)
            current_browse_chars_ascii = ascii_size_table - 1;
    }
    if (input->right())
    {
        current_browse_chars_ascii++;
        refresh_render_cooldown = false;

        if (current_browse_chars_ascii >= ascii_size_table)
            current_browse_chars_ascii = 1;
    }
    if (input->down())
        render->changeAnimationSpeed(render->getAnimationSpeed() + 15);

    if (input->up())
    {
        render->changeAnimationSpeed(render->getAnimationSpeed() - 15);
    }


    if (input->upLong())
    {
        render->renderAnimatedText("+", 1, false, 45);
        char x = getCharFromMyAsciiTable(current_browse_chars_ascii);
        AddNewElementTxtAniamtion(x);
    }

    if (input->leftLong() && input->rightLong())
    {
        render->renderAnimatedText(custom_text, text_length, true);
    }

    if (render->isAnimationDone())
    {
        refresh_render_cooldown = false;
    }

    if (refresh_render_cooldown)
        return;

    refresh_render_cooldown = true;
    Glyph g = _readASCII(current_browse_chars_ascii);
    render->renderGlyph(g);
}

void ActionHandler::resetStates()
{
    text_length = 0;

    refresh_render_cooldown = false;
    current_browse_chars_ascii = 1;
}

void ActionHandler::AddNewElementTxtAniamtion(char e)
{
    text_length++;
    char *t = new char[text_length];

    if (custom_text != nullptr)
    {
        for (short int i = 0; i < text_length; i++)
        {
            t[i] = custom_text[i];
        }

        delete[] custom_text;
    }

    t[text_length-1] = e;

     custom_text = t;
}
