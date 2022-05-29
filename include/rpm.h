#include "Arduino.h"

#define RPM_PIN1 4
#define RPM_PIN2 5
#define RPM_PIN3 6

#define CHANNEL_NUMBER 3

extern int rpm1;
void rpmInit(); // init pcint interrupt
void rpmCal(); // call every 1s to calculate fan rpm
uint32_t rpmGet(uint8_t channel);
uint32_t rpmGetPwm(uint8_t channel);
void setPwm(uint8_t channel,uint8_t pwm);