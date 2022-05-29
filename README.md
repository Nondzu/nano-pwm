# nano-pwm
### PC fan controller based on arduino nano

_______________

##### This controller have 3 independent PWM channels with 25 kHz according to PC fan specification.


##### Serial port (9600bps) is use to communicate with  arduino nano. 

##### AT COMMAND:
* set PWM: <br />
`AT+PWM=$value` - set pwm value for all channels<br />
`AT+PWM=($channel, $value)` - set pwm $value for $channel<br />

* read RPM info: <br />
`AT?RPM` - get RPM values from all channels <br />

Each command must finish be new line character `\n`

example:<br />
`AT+PWM=50` - set all channel PWM to 50%<br />
`AT+PWM=(0,90)` - set channel 0 to 90% PWM. <br />
`AT+PWM=(2,50)` - set channel 2 to 50% PWM. <br />
`AT?RPM` - get rpm value from all channels<br />

-------
#### SCHEMATIC:
Schematic will be available soon. PWM and tachometer pins can by connecting directly to arduino. Additional items are not necessary (resistor or transistors).
here is connection info:<br /><br />
FAN PWM (OUTPUT):<br />
 PIN 9 - PWM output for channel 0<br />
 PIN 10 - PWM output for channel 1<br />
 PIN 3 - PWM output for channel 2<br />
<br />
FAN tachometer (INPUT):<br />
 PIN 4 - RPM CHANNEL 0<br />
 PIN 5 - RPM CHANNEL 1<br />
 PIN 6 - RPM CHANNEL 2<br />


