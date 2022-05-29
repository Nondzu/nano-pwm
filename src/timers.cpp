#include "timers.h"
#include "Arduino.h"
#include "usart.h"

unsigned long previousMillis = 0; // will store last time LED was updated
volatile unsigned long currentMillis = 0;
TimerCallbackPtr timerCallback = nullptr;   //timer 1s event callback 

void timerRegisterCallback(TimerCallbackPtr callback){
    timerCallback = callback;
}

void timer()
{
    currentMillis = millis();
    if (currentMillis - previousMillis >= INTERVAL) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        if (timerCallback != nullptr) {
            timerCallback();
        }
    }
}

void initTimer0()
{
    // set timer0 interrupt at 2kHz
    TCCR0A = 0; // set entire TCCR2A register to 0
    TCCR0B = 0; // same for TCCR2B
    TCNT0 = 0; // initialize counter value to 0

    // set compare match register for 62.5Hz increments
    // OCR0A = (preskaler 1024) * 250 - 1 =  62.5hz
    OCR0A = 249; // = (16*10^6) / (1024 * 250) - 1 (must be <256)
    OCR0B = 22;
    // turn on CTC mode
    TCCR0A |= (1 << WGM01);
    // Set CS01 and CS00 bits for 1024 prescaler
    TCCR0B |= (1 << CS02) | (1 << CS00);
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);
}

void initTimer2()
{
    // Set PWM frequency to about 25khz on pin 3 (timer 2 mode 5, prescale 8, count to 79)
    TIMSK2 = 0;
    TIFR2 = 0;
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << WGM22) | (1 << CS21);
    OCR2A = 79;
    OCR2B = 0;
}

void initTimer1()
{
    // Clear Timer1 control and count registers
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    // Set Timer1 configuration
    // COM1A(1:0) = 0b10   (Output A clear rising/set falling)
    // COM1B(1:0) = 0b00   (Output B normal operation)
    // WGM(13:10) = 0b1010 (Phase correct PWM)
    // ICNC1      = 0b0    (Input capture noise canceler disabled)
    // ICES1      = 0b0    (Input capture edge select disabled)
    // CS(12:10)  = 0b001  (Input clock select = clock/1)

    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << CS10);
    ICR1 = TCNT1_TOP;
}
void setPwmDuty(byte duty) { OCR1A = (word)(duty * TCNT1_TOP) / 100; }

// ********* Interrupts *********

// ISR(TIMER0_COMPA_vect)
// { // change the 0 to 1 for timer1 and 2 for timer2
//   // interrupt commands here
//     static uint8_t timer1s = 0; //  ~1s timer
//     static uint8_t timer2s = 0; //  2s timer good for calculate fan rpm
//     // 62.5hz
//     if (timer1s++ > 62) {
//         timer1s = 0;
//         USART_Transmit('4');
//         // Serial.println("hello");
//     }
//     if (timer2s++ > 125) {
//         timer2s = 0;
//         USART_Transmit('2');
//         // Serial.println("hello");
//     }
// }

// void initTimer0()
// {
//     // set timer0 interrupt at 2kHz
//     TCCR0A = 0; // set entire TCCR2A register to 0
//     TCCR0B = 0; // same for TCCR2B
//     TCNT0 = 0; // initialize counter value to 0
//     // set compare match register for 1khz increments
//     OCR0A = 249; // = (16*10^6) / (1000*64) - 1 (must be <256)
//     // turn on CTC mode
//     TCCR0A |= (1 << WGM01);
//     // Set CS01 and CS00 bits for 64 prescaler
//     TCCR0B |= (1 << CS01) | (1 << CS00);
//     // enable timer compare interrupt
//     TIMSK0 |= (1 << OCIE0A);

//     //preskaler 256 +250 daje 250hz
//     //preskaler 1024 + 250 daje 62.5hz
// }