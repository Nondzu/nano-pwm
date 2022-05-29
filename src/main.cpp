#include "rpm.h"
#include "timers.h"
#include <Arduino.h>
#define LED 13

void at();
void my1sEvent()
{
    rpmCal();   // to calculate rpm value from FAN tachometer
    for (uint8_t i = 0; i < 4; i++) {
        Serial.print("channel ");
        Serial.print(i);
        Serial.print(" rpm: ");
        Serial.println(rpmGet(i));
    }
}

void setup()
{
    pinMode(LED, OUTPUT);

    rpmInit();
    timerInit();
    timerRegisterCallback(my1sEvent);

    // init serial
    Serial.begin(9600);

    setPWM0(40);//450
    setPWM1(75);//840
    setPWM2(15);
}



bool toggle0 = false;
uint8_t pwm = 50;

void loop()
{
    at();
    timer(); // timer function for 1s events
}


//AT commands system
char rx[100];
u8 bufPos = 0;

void at() {
    if (Serial.available() > 0) {
        rx[bufPos] = Serial.read();

        if (rx[bufPos] == '+') {
            pwm++;
        } else if (rx[bufPos] == '-') {
            pwm--;
        }
        setPWM0(pwm);
        setPWM1(pwm);
        setPWM2(pwm);

        if (rx[bufPos] == '\n') {

            at();
            Serial.print(": pwm :");
            Serial.println(pwm);
            bufPos = 0;
        } else
            bufPos++;
    }
}