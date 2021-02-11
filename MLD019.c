#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLD019.h"

#define SERIAL_TTY "/dev/ttyAMA0"
#define MSG_BYTES 5

mld_msg_u mldChecksum(mld_msg_u msg){
    /**Parameteres: mld_msg_u msg - an MLD019 message union representation
     * Return:      mld_msg_u msg - same union with checksum calculated)
     * **/

    char checksum = 0x0;
    for (int i = 1; i < MSG_BYTES; i++) {
        checksum = checksum ^ msg.msg_arr[i];
    }
    msg.msg_struct.checksum = checksum;
    return msg;
}

mld_t mldConfig(char* sertty, int baud) {
    mld_t mld;
    mld.serial_handle = seropen(sertty,9600,0);
}

int mldSendMsg(mld_t mld, mld_msg_u msg) {
    serWrite(mld.serial_handle,msg.msg_hex);
}

mld_msg_u mldRecvMsg(mld_t mld) {
    serRead(mld.serial_handle,);
}

char* mldMsgToString(char* buff, mld_msg_u msg) {
    msg = mldChecksum(msg);
    sprintf(buff,"%0*llX\r",MSG_BYTES*2, msg.msg_hex);   //convert augmented number to 4-byte hex string with carriage return

    return buff;
}   

mld_msg_u mldStringToMsg(char* str) {
    mld_msg_u msg;
    msg.msg_hex = strtoll(str,NULL,16);
    return msg;
}

/**
mld_driver_t mldConfig(char* sertty, unsigned int baud) {
    int h = serOpen(sertty, baud, 0);
    return h; 
}
**/
mldLinkControl
void checkStatus(int status, char* error_str) {
    if (status < 0) {
        
        char str[] = " Error %d\n";

        char* out_str = (char*) malloc(sizeof(error_str) + sizeof(str) + 1);
        strcpy(out_str,error_str);
        strcat(out_str, str);
        printf(out_str);
        free(out_str);
        exit(status);
    }
    else {
        printf("%s status: %d\n", error_str, status);
    }
}


int main() {
    char* send_buff = mldHexCmdString(0x04FFFF00);
    printf("%s\n",send_buff);
    printf("%X\n", send_buff[10]);
    free(send_buff);
}