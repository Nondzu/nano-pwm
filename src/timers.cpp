#include "timers.h"
#include "usart.h"

unsigned long previousMillis = 0; // will store last time LED was updated
volatile unsigned long currentMillis = 0;
TimerCallbackPtr timerCallback = nullptr; // timer 1s event callback

void timerRegisterCallback(TimerCallbackPtr callback) { timerCallback = callback; }

void timerInit()
{
    initTimer2();
    initTimer1();
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

void initTimer1()
{
    // Set PWM frequency to  25khz
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << CS10) | (1 << WGM13);
    ICR1 = 320;
    OCR1A = 0;
    OCR1B = 0;

    // set pins to output mode
    pinMode(OC1A_PIN, OUTPUT);
    pinMode(OC1B_PIN, OUTPUT);
}

void initTimer2()
{
    // Set PWM frequency to  25khz on pin 3 (timer 2 mode 5, prescale 8, count to 79)
    TIMSK2 = 0;
    TIFR2 = 0;
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << WGM22) | (1 << CS21);
    OCR2A = 79;
    OCR2B = 0;

    // set pin to output mode
    pinMode(OC2B_PIN, OUTPUT);
}

void setPWM0(uint8_t pwm)
{
    pwm = pwm > 100 ? 100 : pwm;
    OCR1A = (uint16_t)(((uint16_t)320 * pwm) / 100);
}

void setPWM1(uint8_t pwm)
{
    pwm = pwm > 100 ? 100 : pwm;
    OCR1B = (uint16_t)(((uint16_t)320 * pwm) / 100);
}

void setPWM2(uint8_t pwm)
{
    pwm = pwm > 100 ? 100 : pwm;
    OCR2B = (uint8_t)(((uint16_t)79 * pwm) / 100);
}