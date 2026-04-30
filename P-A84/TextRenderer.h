#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "ASCII.h"
#include "pins.h"
#include <Arduino.h>
#include <TimerKernel.h>

class TextRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

    /// @brief renders glyph 8x8 on display
    /// @param glyph table of 8 uint8_t values, each for one row. SIZE: 8 values
    void renderGlyph(Glyph &glyph);

    /// @brief 
    /// @param character give specified character to render
    void renderASCII(char character);

    void renderAnimatedText(char* text, int text_length, int animation_speed_ms = 140, bool loop_animation = false);

    void update();
private:

    Glyph glyph_to_render;
    // If TRUE: render glyph, IF FALSE: render aniamtion
    bool render_glyph;
    bool render_animation;

    //Animation vars
    char* animated_text;
    Glyph anim_glyph_1;
    Glyph anim_glyph_2;
    int length;
    int iterator;

};



#endif