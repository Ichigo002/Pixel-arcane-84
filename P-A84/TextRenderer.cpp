#include "TextRenderer.h"

TextRenderer::TextRenderer(/* args */)
{
    render_glyph = false;
    render_animation = false;
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::renderGlyph(Glyph &glyph)
{
    glyph_to_render = glyph;
    render_glyph = true;
    render_animation = false;
}

void TextRenderer::renderASCII(char character)
{
    glyph_to_render = _readASCII(getAsciiTablePosition(character));
    render_glyph = true;
    render_animation = false;
}

void TextRenderer::renderAnimatedText(char *text, int text_length, int animation_speed_ms, bool loop_animation)
{
    animated_text = text;
    length = text_length;

    current_char = 0;

    anim_glyph_1 = getCharToAnimation(current_char);
    anim_glyph_2 = getCharToAnimation(current_char + 1);

    render_glyph = false;
    render_animation = true;
}

void TextRenderer::update()
{
    if (render_glyph)
    {
        for (byte i = 0; i < 8; i++)
        {
            digitalWrite(rowLatchPin, LOW);
            digitalWrite(colLatchPin, LOW);
            shiftOut(rowDataPin, rowClockPin, LSBFIRST, (1 << i));
            shiftOut(colDataPin, colClockPin, MSBFIRST, glyph_to_render.raw_ascii[i]);
            digitalWrite(rowLatchPin, HIGH);
            digitalWrite(colLatchPin, HIGH);
            delay(1);
        }
    }
    if (render_animation)
    {
        


        for (byte i = 0; i < 8; i++)
        {
            digitalWrite(rowLatchPin, LOW);
            digitalWrite(colLatchPin, LOW);
            shiftOut(rowDataPin, rowClockPin, LSBFIRST, (1 << i));
            shiftOut(colDataPin, colClockPin, MSBFIRST, glyph_to_render.raw_ascii[i]);
            digitalWrite(rowLatchPin, HIGH);
            digitalWrite(colLatchPin, HIGH);
            delay(1);
        }
    }
}

Glyph TextRenderer::getCharToAnimation(int char_no)
{
    return _readASCII(getAsciiTablePosition(animated_text[char_no]));
}