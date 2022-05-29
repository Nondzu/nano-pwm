#include "rpm.h"
#include "Arduino.h"
#include "PinChangeInterrupt.h"


struct tachometer {
    uint32_t rpm;
    uint32_t rpmCnt;
};

struct tachometer tacho[CHANNEL_NUMBER];

void rpmCal()
{
    for (uint8_t i = 0; i < CHANNEL_NUMBER; i++) {
        tacho[i].rpm = tacho[i].rpmCnt * 60 / 2;
        tacho[i].rpmCnt = 0;
    }
}

void interruptRPM1() { tacho[0].rpmCnt++; }
void interruptRPM2() { tacho[1].rpmCnt++; };
void interruptRPM3() { tacho[2].rpmCnt++; };

void rpmInit()
{
    // pullup pins
    pinMode(RPM_PIN1, INPUT_PULLUP);
    pinMode(RPM_PIN2, INPUT_PULLUP);
    pinMode(RPM_PIN3, INPUT_PULLUP);
    // init pcint interrupt
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(RPM_PIN1), interruptRPM1, FALLING);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(RPM_PIN2), interruptRPM2, FALLING);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(RPM_PIN3), interruptRPM3, FALLING);
}

uint32_t rpmGet(uint8_t channel) { return channel < CHANNEL_NUMBER ? tacho[channel].rpm : 0; }