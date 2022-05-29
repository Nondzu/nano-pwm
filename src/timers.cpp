#include "timers.h"
#include "Arduino.h"
#include "usart.h"
void initTimer0()
{
    // set timer0 interrupt at 2kHz
    TCCR0A = 0; // set entire TCCR2A register to 0
    TCCR0B = 0; // same for TCCR2B
    TCNT0 = 0; // initialize counter value to 0
    // set compare match register for 1khz increments
    OCR0A = 249; // = (16*10^6) / (1000*64) - 1 (must be <256)
    // turn on CTC mode
    TCCR0A |= (1 << WGM01);
    // Set CS01 and CS00 bits for 64 prescaler
    TCCR0B |= (1 << CS01) | (1 << CS00);
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);
}

//timer 0 interrupt
ISR(TIMER0_COMPA_vect)
{ // change the 0 to 1 for timer1 and 2 for timer2
  // interrupt commands here
    static int cnt = 0;
    if (cnt++ > 1000) {
        cnt = 0;
        USART_Transmit('4');
    }
}