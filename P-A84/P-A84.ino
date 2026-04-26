#include <Arduino.h>
#include "pins.h"

void setupPins()
{
    pinMode(rowDataPin, OUTPUT);
    pinMode(rowClockPin, OUTPUT);
    pinMode(rowLatchPin, OUTPUT);

    pinMode(colDataPin, OUTPUT);
    pinMode(colClockPin, OUTPUT);
    pinMode(colLatchPin, OUTPUT);

    pinMode(btnLeftPin, INPUT_PULLUP);
    pinMode(btnOkPin, INPUT_PULLUP);
    pinMode(btnCancelPin, INPUT_PULLUP);
    pinMode(btnRightPin, INPUT_PULLUP);
}

void setup() 
{
    setupPins();

}

void loop() 
{
    delay(100);
    digitalWrite(colLatchPin, LOW);
    digitalWrite(rowLatchPin, LOW);
    delay(100);
    shiftOut(colDataPin, colClockPin, MSBFIRST, 0x01111110);
    delay(100);
    shiftOut(rowDataPin, rowClockPin, MSBFIRST, 0x01111110);

    delay(100);
    digitalWrite(colLatchPin, HIGH);
    digitalWrite(rowLatchPin, HIGH);
    delay(1000);
}
