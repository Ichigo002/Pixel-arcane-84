#include "ASCII.h"

int getAsciiTablePosition(char &c)
{
    if (c >= 65 && c <= 90)
        return c - 64; // - 65 + 1 (becuase Not found character)
    if (c >= 48 && c <= 57)
        return c - 38;

    return 0;
}

Glyph _readASCII(short int ascii_number)
{
    Glyph m;

    if(ascii_number > 43 && ascii_number < 0)
        return _readASCII(NOT_FOUND_CHAR);

    for (byte i = 0; i < 8; i++)
    {
        m.raw_ascii[i] = pgm_read_byte(&(ascii_table[ascii_number][i]));
    }

    return m;
}