#include <Arduino.h>
#include "timers.h"
#define LED 13
const byte OC1A_PIN = 9;
const byte OC1B_PIN = 10;

const word PWM_FREQ_HZ = 25000; // Adjust this value to adjust the frequency (Frequency in HZ!) (Set currently to 25kHZ)
const word TCNT1_TOP = 16000000 / (2 * PWM_FREQ_HZ);
int cnt = 0;
void setPwmDuty(byte duty) { OCR1A = (word)(duty * TCNT1_TOP) / 100; }
void isr() // interrupt service routine
{
    cnt++;
}

void initUsart();
void USART_Transmit(unsigned char data);
void setup()
{
    cli(); // stop interrupts
    pinMode(OC1A_PIN, OUTPUT);
    pinMode(OC1B_PIN, OUTPUT);
    pinMode(LED, OUTPUT);

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

    // init isr
    digitalWrite(2, HIGH); // Instead of using a pull up resistor
    attachInterrupt(0, isr, RISING); // attaching the interrupt

    setPwmDuty(75); // set default 75% FAN PWM

    // init serial
    // Serial.begin(9600);
    initTimer0();
    initUsart();
    sei(); // allow interrupts
}

bool toggle1 = false;
char rx[100];
u8 bufPos = 0;


bool toggle0 = false;






void loop()
{

}

