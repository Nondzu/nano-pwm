#include "rpm.h"
#include "Arduino.h"
#include "PinChangeInterrupt.h"

#define INTERRUPT_PIN 2

int rpm1 = 0;
void interruptRoutine();

void rpmInit()
{
    // init pcint interrupt
    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(INTERRUPT_PIN), interruptRoutine, FALLING);
}

void interruptRoutine()
{
    //   ?digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    rpm1++;
}