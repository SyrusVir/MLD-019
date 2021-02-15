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

    uint64_t hex_num = 0xA6239F57AA;
    if (argc > 1) {
        hex_num = strtoll(argv[1],NULL,16);
    }

    mld_msg_u recv_msg = mldExecuteCMD(mld,hex_num);

    if (mldValidateMsg(recv_msg) != 0) {
        printf("ERROR ");
    }
    
    printf("mldLinkControl=%d\n", mldLinkControl(mld));
    serClose(mld.serial_handle);
    gpioTerminate();
    return 0;
}