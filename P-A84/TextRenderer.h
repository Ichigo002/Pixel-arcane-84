#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "ASCII.h"
#include "pins.h"
#include <Arduino.h>

#define BRIGHTNBESS_DROP_VAL 220

class TextRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

    void begin();

    /// @brief renders glyph 8x8 on display
    /// @param glyph table of 8 uint8_t values, each for one row. SIZE: 8 values
    void renderGlyph(Glyph &glyph);

    /// @brief
    /// @param character give specified character to render
    void renderASCII(char character);

    void renderAnimatedText(char *text, int text_length, bool loop_animation = false, int animation_speed_ms = 100);

    void changeAnimationSpeed(int animation_speed_ms);

    int getAnimationSpeed();

    void breakLoopAnimation();

    bool isAnimationDone();

    void increaseBrightness();
    
    void decreaseBrightness();

    void update();

private:
    Glyph glyph_to_render;

    bool render_animation;

    short int brightness; // value between 1 - 1500;

    // Animation vars
    char *animated_text;
    Glyph anim_glyph;
    int animation_speed_ms;
    int length;
    int current_char;
    int bit_shifter;
    uint32_t animation_timestamp;
    bool final_character;
    bool loop_animation;

    Glyph getCharToAnimation(int char_no, bool force_space = false);
};

#endif