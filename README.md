# nano-pwm
Arduino nano pwm controller for PC fan



AT COMMAND:

set PWM info
AT+PWM=$value - set pwm value for all channels
AT+PWM=($channel, $value) - set pwm $value for $channel

read RPM info
AT?RPM - get RPM values from all channels
AT?RPM=($channel) - get RPM value from $channel

each command must finish be new line character '\n'

example:

AT+PWM=50 - set all channel PWM to 50%
AT+PWM=(1,100) - set channel 0 PWM to 100%

AT?RPM=(2) - receive rpm value from channel 2