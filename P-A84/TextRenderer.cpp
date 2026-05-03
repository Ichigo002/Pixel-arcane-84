#include "TextRenderer.h"

TextRenderer::TextRenderer(/* args */)
{
    render_animation = false;
    brightness = 100;
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::begin()
{
    pinMode(rowDataPin, OUTPUT);
    pinMode(rowClockPin, OUTPUT);
    pinMode(rowLatchPin, OUTPUT);

    pinMode(colDataPin, OUTPUT);
    pinMode(colClockPin, OUTPUT);
    pinMode(colLatchPin, OUTPUT);
}

void TextRenderer::renderGlyph(Glyph &glyph)
{
    glyph_to_render = glyph;
    render_animation = false;
}

void TextRenderer::renderASCII(char character)
{
    glyph_to_render = _readASCII(getAsciiTablePosition(character));
    render_animation = false;
}

void TextRenderer::renderAnimatedText(char *text, int text_length, bool loop_animation, int animation_speed_ms)
{
    this->animation_speed_ms = animation_speed_ms;
    this->loop_animation = loop_animation;
    animated_text = text;
    length = text_length;

    current_char = 0;
    bit_shifter = 8;

    anim_glyph = getCharToAnimation(current_char);

    
    glyph_to_render = Glyph();
    for (byte i = 0; i < 8; i++)
    {
        glyph_to_render.raw_ascii[i] = 0;
    }

    render_animation = true;
    final_character = false;
}

void TextRenderer::changeAnimationSpeed(int animation_speed_ms)
{
    if(animation_speed_ms < 0)
        return;
    this->animation_speed_ms = animation_speed_ms;
}

int TextRenderer::getAnimationSpeed()
{
    return animation_speed_ms;
}

void TextRenderer::breakLoopAnimation()
{
    loop_animation = false;
}

bool TextRenderer::isAnimationDone()
{
    return !render_animation;
}

void TextRenderer::increaseBrightness()
{
    brightness += BRIGHTNBESS_DROP_VAL;
    if(brightness > 1500)
        brightness = 1500;
}

void TextRenderer::decreaseBrightness()
{
    brightness -= BRIGHTNBESS_DROP_VAL;
    if(brightness - BRIGHTNBESS_DROP_VAL < 0)
        brightness = 1; 
}

void TextRenderer::update()
{
    if (render_animation && (millis() - animation_timestamp >= animation_speed_ms))
    {
        for (byte i = 0; i < 8; i++)
        {
            glyph_to_render.raw_ascii[i] =
                (glyph_to_render.raw_ascii[i] << 1) | ((anim_glyph.raw_ascii[i] >> bit_shifter) & 1);
        }

        bit_shifter--;
        if (bit_shifter < 0)
        {
            current_char++;

            if (final_character)
            {
                if (loop_animation)
                {
                    current_char = 0;
                    final_character = false;
                }
                else
                {
                    render_animation = false;
                }
            }

            anim_glyph = getCharToAnimation(current_char, (final_character && loop_animation));
            bit_shifter = 8;
        }

        animation_timestamp = millis();
    }

    for (byte i = 0; i < 8; i++)
    {
        digitalWrite(rowLatchPin, LOW);
        digitalWrite(colLatchPin, LOW);
        shiftOut(rowDataPin, rowClockPin, LSBFIRST, (1 << i));
        shiftOut(colDataPin, colClockPin, MSBFIRST, glyph_to_render.raw_ascii[i]);
        digitalWrite(rowLatchPin, HIGH);
        digitalWrite(colLatchPin, HIGH);
        delayMicroseconds(brightness);

        digitalWrite(rowLatchPin, LOW);
        digitalWrite(colLatchPin, LOW);
        shiftOut(rowDataPin, rowClockPin, LSBFIRST, 0);
        shiftOut(colDataPin, colClockPin, MSBFIRST, 0); // 1 , 1500
        digitalWrite(rowLatchPin, HIGH);
        digitalWrite(colLatchPin, HIGH);

        delayMicroseconds(1500 - brightness);
    }
}

Glyph TextRenderer::getCharToAnimation(int char_no, bool force_space)
{
    if (char_no >= length)
    {
        final_character = true;
        return Glyph();
    }

    if (force_space)
    {
        char space = ' ';
        return _readASCII(getAsciiTablePosition(space));
    }

    return _readASCII(getAsciiTablePosition(animated_text[char_no]));
}