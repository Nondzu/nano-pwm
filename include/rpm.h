#include "Arduino.h"

extern int rpm1;

void rpmInit(); // init pcint interrupt

void rpmCal(); // call every 1s to calculate fan rpm

uint32_t rpmGet(uint8_t channel);