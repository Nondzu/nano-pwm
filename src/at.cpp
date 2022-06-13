
#include "at.h"
#include "timers.h"
#include "rpm.h"
void printPwmInfo();
void printRpmInfo();

String rxBuf;
void at()
{
    if (Serial.available() > 0) {
        char c = Serial.read(); // gets one byte from serial buffer
        Serial.print(c); // echo on serial port
        rxBuf += c;

        if (c == '\n') {    //detect new line 
            if (rxBuf.indexOf(AT_SET) >= 0) { // AT SET
                if (rxBuf.indexOf(PWM) >= 0) { // AT SET PWM
                    if (rxBuf.indexOf("=(") >= 0) {
                        String ch = rxBuf.substring(rxBuf.indexOf("(") + 1, rxBuf.indexOf(","));
                        String pwm = rxBuf.substring(rxBuf.indexOf(",") + 1, rxBuf.indexOf(")"));

                        setPWM(ch.toInt(), pwm.toInt());

                        Serial.println(OK);
                        printPwmInfo();
                    } else if (rxBuf.indexOf("=") >= 0) {
                        rxBuf = rxBuf.substring(rxBuf.indexOf("=") + 1);
                        long pwm = rxBuf.toInt();
                        setPWM(255, pwm);

                        Serial.println(OK);
                        printPwmInfo();

                    } else {
                        Serial.println(ERROR);
                    }
                }
            } else if (rxBuf.indexOf(AT_GET_RPM) >= 0) { // AT GET
                printRpmInfo();
            } else {
                Serial.println(ERROR);
            }

            rxBuf = ""; //clear rx buf
        }
    }
}


void printPwmInfo()
{
    for (uint8_t i = 0; i < 3; i++) {
        Serial.print(F("channel "));
        Serial.print(i);
        Serial.print(F(" pwm: "));
        Serial.println(rpmGetPwm(i));
    }
}
void printRpmInfo()
{
    for (uint8_t i = 0; i < 3; i++) {
        Serial.print(F("channel "));
        Serial.print(i);
        Serial.print(F(" rpm: "));
        Serial.println(rpmGet(i));
    }
}
