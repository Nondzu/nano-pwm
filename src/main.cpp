#include "Wstring.h"
#include "rpm.h"
#include "at.h"
#include "timers.h"
#include <Arduino.h>
#define LED 13
bool toggle0 = false;

void my1sEvent()
{
    rpmCal(); // to calculate rpm value from FAN tachometer

    digitalWrite(LED, toggle0); //led blink 
    toggle0 = !toggle0; 
}

void setup()
{
    pinMode(LED, OUTPUT);

    rpmInit();
    timerInit();
    timerRegisterCallback(my1sEvent);

    // init serial
    Serial.begin(9600);

    setPWM0(50); // 450
    setPWM1(50); // 840
    setPWM2(50);
}

void loop()
{
    at();
    timer(); // timer function for 1s events
}

