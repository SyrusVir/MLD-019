#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MLD019.h"

#define SERIAL_TERM "/dev/ttyAMA0" //target PL011 UART module
#define BAUD 9600


int main(int argc, char** argv) {
    gpioInitialise();

    mld_t mld;
    mld.serial_handle = serOpen(SERIAL_TERM, BAUD, 0);

    char c;
    do 
    {    
        printf("\'c\' to exit | any other char to execute mldLinkControl\n");
        scanf("%c",&c);
        printf("mldLinkControl=%d\n", mldLinkControl(mld));
    } while (c != 'c');

    serClose(mld.serial_handle);
    gpioTerminate();
    return 0;
}