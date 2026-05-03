#include "ASCII.h"

const char asciiLUT[46] = {
    0,    // 0 (unused)

    // A-Z -> 1–26
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z',

    // 27–36 -> 0–9
    '0','1','2','3','4','5','6','7','8','9',

    // 37–45 -> special chars
    ' ', // 37
    '!', // 38
    '?', // 39
    ')', // 40
    '(', // 41
    '#', // 42
    ',', // 43
    '.', // 44
    '-'  // 45
};

char getCharFromMyAsciiTable(int i)
{
    if (i >= 0 && i < 46)
        return asciiLUT[i];

    return '?';
}

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