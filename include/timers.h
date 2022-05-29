#include "Arduino.h"
// timer 1 pins 
#define OC1A_PIN 9
#define OC1B_PIN 10

// timer 2 pins 
#define OC2B_PIN 3

#define INTERVAL 1000 // interval at which to blink (milliseconds)
typedef void (*TimerCallbackPtr)(void);


void initTimer1();
void initTimer2();

void setPWM0(uint8_t pwm);  //pin 9
void setPWM1(uint8_t pwm);  //pin 10
void setPWM2(uint8_t pwm);  //pin 3


void timerRegisterCallback(TimerCallbackPtr callback);
void timer();
// void timerRegisterCalback()

void timerInit();

