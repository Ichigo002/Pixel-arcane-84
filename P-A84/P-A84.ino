#include <Arduino.h>
#include "pins.h"
#include "TextRenderer.h"
#include <avr/pgmspace.h>
#include <TimerKernel.h>

TextRenderer renderer;
TimerKernel timer_change_char;
int i = 0;

void setupPins()
{
    pinMode(rowDataPin, OUTPUT);
    pinMode(rowClockPin, OUTPUT);
    pinMode(rowLatchPin, OUTPUT);

    pinMode(colDataPin, OUTPUT);
    pinMode(colClockPin, OUTPUT);
    pinMode(colLatchPin, OUTPUT);

    pinMode(btnLeftPin, INPUT);
    pinMode(btnOkPin, INPUT);
    pinMode(btnCancelPin, INPUT);
    pinMode(btnRightPin, INPUT);
}

void setup() 
{
    setupPins();
    renderer.renderAnimatedText("XD", 2, 100, true);
    //renderer.renderASCII(' ');
}

void loop() 
{
    // if(timer_change_char.hasExpired(1000))
    // {
    //     if(i>44)
    //         i = 0;
    //     Glyph g = _readASCII(i);
    //     renderer.renderGlyph(g);
    //     i++;
    //     timer_change_char.resetHasExpired();
    // }
    renderer.update();
}
