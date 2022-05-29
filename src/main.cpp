#include "timers.h"
#include <Arduino.h>
#define LED 13

void my1sEvent() { 
    Serial.println("1s callback");
}

void setup()
{
    // cli(); // stop interrupts
    pinMode(OC1A_PIN, OUTPUT);
    pinMode(OC1B_PIN, OUTPUT);
    pinMode(LED, OUTPUT);

    // init isr
    digitalWrite(2, HIGH); // Instead of using a pull up resistor

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

    timer();// timer function for 1s events
}