#include "rpm.h"
#include "timers.h"
#include <Arduino.h>
#define LED 13

void my1sEvent()
{
    // Serial.println("1s callback");
    // Serial.println(rpm1);
    rpmCal();

    for (uint8_t i = 0; i < 4; i++) {
        Serial.print("channel ");
        Serial.print(i);
        Serial.print(" rpm: ");
        Serial.println(rpmGet(i));
    }
}

void setup()
{
    pinMode(OC1A_PIN, OUTPUT);
    pinMode(OC1B_PIN, OUTPUT);
    pinMode(LED, OUTPUT);

    // init isr
    digitalWrite(2, HIGH); // Instead of using a pull up resistor
    rpmInit();

    timerRegisterCallback(my1sEvent);

    // init serial
    Serial.begin(9600);
}

bool toggle1 = false;
char rx[100];
u8 bufPos = 0;
bool toggle0 = false;

void loop()
{
    if (Serial.available() > 0) {
        rx[bufPos] = Serial.read();
        Serial.println("reading");
        if (rx[bufPos] == '\n') {
            Serial.println("new line");
            bufPos = 0;
        } else
            bufPos++;
    }

    timer(); // timer function for 1s events
}