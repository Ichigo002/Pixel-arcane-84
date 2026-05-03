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
    TextRenderer* render;
    InputHandler *input;

    bool refresh_render_cooldown;
    short int current_browse_chars_ascii;
};




#endif