// timer 1
#define OC1A_PIN 9
#define OC1B_PIN 10
#define PWM_FREQ_HZ 25000L // Adjust this value to adjust the frequency (Frequency in HZ!) (Set currently to 25kHZ)
#define TCNT1_TOP (16000000L / (2L * PWM_FREQ_HZ))
#define INTERVAL 1000 // interval at which to blink (milliseconds)

void initTimer1();

typedef void (*TimerCallbackPtr)(void);

void timerRegisterCallback(TimerCallbackPtr callback);

void timer();
// void timerRegisterCalback()