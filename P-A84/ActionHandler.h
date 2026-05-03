#ifndef ACTION_HANDLER_H
#define ACTION_HANDLER_H

#include "TextRenderer.h"
#include "InputHandler.h"
#include "ASCII.h"

class ActionHandler
{
public:
    ActionHandler(TextRenderer* render, InputHandler* input);
    ~ActionHandler();

    void runBrowseChars();
    void runExampleAnimation();
    void runCustomAnimation();

    void resetStates();

private:
    void AddNewElementTxtAniamtion(char e);

    TextRenderer* render;
    InputHandler *input;

    short int text_length;
    char* custom_text;

    bool refresh_render_cooldown;
    short int current_browse_chars_ascii;
};




#endif