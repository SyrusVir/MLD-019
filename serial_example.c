#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <MLD019.h>

#define SERIAL_TERM "/dev/ttyAMA0" //target PL011 UART module
#define BAUD 9600

int main() {
    checkStatus(gpioInitialise(), "gpioInitialise");

    mld_t mld;
    mld.serial_handle = serOpen(SERIAL_TERM, BAUD, 0);
    checkStatus(mld.serial_handle, "serOpen");

    mld_msg_u out_msg;
    out_msg.msg_hex = 0x04000000;
    out_msg.msg_struct.checksum = mldChecksum(out_msg);

    char in_data[11];
    mldSendMsg(mld, out_msg);
    while(!serDataAvailable(mld.serial_handle)) {};
    mld_msg_u recv_msg = mldRecvMsg(mld);
    
    char rec_checksum = mldChecksum(recv_msg);
    if (rec_checksum != recv_msg.msg_struct.checksum) {
        printf("RECEIVED MESSAGE CHECKSUM ERROR\n");
    }
    else {
        printf("recv_msg=%llX",recv_msg.msg_hex);
    }

    serClose(mld.serial_handle);
    gpioTerminate();
    return 0;
}