#include "ASCII.h"

int getAsciiTablePosition(char &c)
{

    if (c >= 48 && c <= 57)
        return c - 21;

    if (c >= 65 && c <= 90)
        return c - 64;

    switch (c)
    {
    case 32: // space
        return 37;
    case 33: // !
        return 38;
    case 63: // ?
        return 39;
    case 41: // ) :)
        return 40;
    case 40: // ( :(
        return 41;
    case 35: // # human pivot!
        return 42;
    case 44: // ,
        return 43;
    case 46: // .
        return 44;
    case 45:
        return 45;
        // ADD HERE NEW TRANSLATION TO SEE CARACTER ON SCREEN

    default:
        return 0;
    }
}

Glyph _readASCII(short int ascii_number)
{
    Glyph m;
                    
    if (ascii_number >= ascii_size_table && ascii_number < 0)
        return _readASCII(NOT_FOUND_CHAR);

    for (byte i = 0; i < 8; i++)
    {
        m.raw_ascii[i] = pgm_read_byte(&(ascii_table[ascii_number][i]));
    }

    return m;
}