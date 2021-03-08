#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MLD019.h"

#define SERIAL_TERM "/dev/ttyAMA0" //target PL011 UART module
#define BAUD 9600

#define ENABLE_PIN 33
#define PULSE_PIN 33

int main(int argc, char** argv) {
    gpioInitialise();

    mld_t mld;
    mld.serial_handle = serOpen(SERIAL_TERM, BAUD, 0);

    gpioSetMode(ENABLE_PIN, PI_OUTPUT);
    //gpioSetMode(PULSE_PIN, PI_OUTPUT);

    //disable
    bool enable_state = 0;
    gpioWrite(ENABLE_PIN,0);

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
            default:
                break;
        }
    } while (c != 'c');

    serClose(mld.serial_handle);
    gpioTerminate();
    return 0;
}