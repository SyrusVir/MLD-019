#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MLD019.h"

#define SERIAL_TERM "/dev/ttyAMA0" //target PL011 UART module
#define BAUD 9600

#define LASER_ENABLE_PIN 26      // physical pin 37
#define LASER_SHUTTER_PIN 6      // physical pin 31
#define LASER_PULSE_PIN 23       // physical pin 16
#define LASER_PULSE_FREQ 10000    
#define LASER_PULSE_PERIOD_USEC 1000000/LASER_PULSE_FREQ   
#define LASER_PULSE_WIDTH_USEC 10
#define LASER_PULSE_DUTY (unsigned int)(LASER_PULSE_WIDTH_USEC / 1000000.0 * LASER_PULSE_FREQ * PI_HW_PWM_RANGE)
#define LASER_PULSE_DURATION_SEC 30

int main(int argc, char** argv) {
    gpioInitialise();

    mld_t* mld = mldInit(SERIAL_TERM);
    // mld.serial_handle = serOpen(SERIAL_TERM, BAUD, 0);

    printf("mld mode = %X\n",mld->mode);
    printf("mld trigger = %X\n",mld->trigger_source);

    gpioSetMode(LASER_ENABLE_PIN, PI_OUTPUT);
    gpioSetMode(LASER_SHUTTER_PIN, PI_OUTPUT);

    //disable
    bool enable_state = 0;
    bool shutter_state = 0;
    gpioWrite(LASER_ENABLE_PIN,0);
    gpioWrite(LASER_SHUTTER_PIN,0);

    gpioSetMode(LASER_PULSE_PIN, PI_OUTPUT);
    
    char c;
    do 
    {    
        printf("\'c\' - exit\n");
        printf("\'l\' - mldlinkcontrol\n");
        printf("\'s\' - mldStatus\n");
        printf("\'v\' - mldVLD\n");
        printf("\'b\' - mldBoardTemp\n");
        printf("\'f\' - mldFirmware\n");
        printf("\'o\' - mldCheckConfig\n");
        printf("\'d\' - mldCaseTemp\n");
        printf("\'E\' - toggle laser enable\n");
        printf("\'S\' - toggle laser shutter\n");
        printf("\'P\' - emit laser pulses\n");

        scanf("%c%*c",&c);
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
                printf("gpioWrite=%d\n",gpioWrite(LASER_ENABLE_PIN, enable_state));
                printf("enable_state=%d\n",enable_state);
                break;
            case 'S':
                shutter_state = !shutter_state;
                printf("gpioWrite=%d\n",gpioWrite(LASER_SHUTTER_PIN, shutter_state));
                printf("shutter_state=%d\n",shutter_state);
                gpioDelay(500000);
                break;
            case 'P':;
                // gpioSetPWMfrequency(LASER_PULSE_PIN,LASER_PULSE_FREQ);
                uint32_t start_tick = gpioTick();
                uint32_t end_tick = start_tick + LASER_PULSE_DURATION_SEC * 1000000; //add 200 ms
                // gpioPWM(LASER_PULSE_PIN,255/2);
                //gpioHardwarePWM(LASER_PULSE_PIN, LASER_PULSE_FREQ, LASER_PULSE_DUTY);
                while (gpioTick() < end_tick) {
                    gpioWrite(LASER_PULSE_PIN,1);
                    gpioDelay(500);
                    gpioWrite(LASER_PULSE_PIN,0);
                    gpioDelay(500);

                }
                //gpioPWM(LASER_PULSE_PIN,0);
                //gpioHardwarePWM(LASER_PULSE_PIN, LASER_PULSE_FREQ, LASER_PULSE_DUTY);
                break;
            default:
                break;
        }
    } while (c != 'c');

    mldClose(mld);
    gpioTerminate();
    return 0;
}