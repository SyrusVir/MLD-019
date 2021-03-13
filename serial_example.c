#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MLD019.h"

#define SERIAL_TERM "/dev/ttyAMA0" //target PL011 UART module
#define BAUD 9600

#define ENABLE_PIN 6 //physical pin 31
#define PULSE_PIN 26 //physical pin 37
#define SHUTTER_PIN 5 //physical pin 29

int main(int argc, char** argv) {
    gpioInitialise();

    mld_t mld;
    mld.serial_handle = serOpen(SERIAL_TERM, BAUD, 0);

    gpioSetMode(ENABLE_PIN, PI_OUTPUT);
    gpioSetMode(SHUTTER_PIN, PI_OUTPUT);

    //disable
    bool enable_state = 0;
    bool shutter_state = 0;
    gpioWrite(ENABLE_PIN,0);
    gpioWrite(SHUTTER_PIN,0);

    gpioSetMode(PULSE_PIN, PI_OUTPUT);
    
    char c;
    do 
    {    
        printf("\'c\' to exit | any other char to execute mldLinkControl\n");
        scanf("%c",&c);
        switch (c)
        {
            case 'l':
                printf("mldLinkControl=%d\n", mldLinkControl(mld));
                break;
            case 's':
                printf("mldStatus=%d\n", mldStatus(mld));
                break;
            case 'v':
                printf("mldVLD=%g\n", mldVLD(mld));
                break;
            case 'b':
                printf("mldBoarTemp=%g\n", mldBoardTemp(mld));
                break;
            case 'f':
                printf("mldFirmware=%x\n", mldFirmware(mld));
                break;
            case 'o':
                printf("mldCheckConfig=%X\n", mldCheckConfig(mld));
                break;
            case 'd':
                printf("mldCaseTemp=%g\n", mldCaseTemp(mld));
                break;
            case 'E':
                enable_state = !enable_state;
                printf("gpioWrite=%d\n",gpioWrite(ENABLE_PIN, enable_state));
                printf("enable_state=%d\n",enable_state);
                break;
            case 'S':
                shutter_state = !shutter_state;
                printf("gpioWrite=%d\n",gpioWrite(SHUTTER_PIN, shutter_state));
                printf("shutter_state=%d\n",shutter_state);
                gpioDelay(500000);
                break;
            case 'P':
                gpioSetPWMfrequency(PULSE_PIN,1000);
                uint32_t start_tick = gpioTick();
                uint32_t end_tick = start_tick + 1000000; //add 200 ms
                gpioPWM(PULSE_PIN,255/2);
                while (gpioTick() < end_tick) {}
                gpioPWM(PULSE_PIN,0);
                printf("gpioTrigger=%d\n",gpioTrigger(PULSE_PIN,3,1));
                break;
            default:
                break;
        }
    } while (c != 'c');

    serClose(mld.serial_handle);
    gpioTerminate();
    return 0;
}