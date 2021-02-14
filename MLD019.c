#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include <string.h>
#include "MLD019.h"

#define SERIAL_TTY "/dev/ttyAMA0"
#define MSG_BYTES 6 //5-byte command + carriage return
#define BAUD 9600   //baud rate defined b MLD-019 datasheet

void checkStatus(int status, char* error_str) {
    /** Utility function used to check return values of functions and printing error messages
     *  if any occur **/
    
    if (status < 0) {
        
        char str[] = " Error %d\n";

        char* out_str = (char*) malloc(sizeof(error_str) + sizeof(str) + 1);
        strcpy(out_str,error_str);
        strcat(out_str, str);
        printf("%s",out_str);
        free(out_str);
        exit(status);
    }
    else {
        printf("%s status: %d\n", error_str, status);
    }
}

char mldChecksum(mld_msg_u msg){
    /**Parameteres: mld_msg_u msg - an MLD019 message union representation
     * Return:      char checksum - checksum
     * 
     * Description: Using the struct representation, calculate the checksum as the
     *              XOR of the uppre 4-bytes (header and data). 
     * **/

    char checksum = 0x0;
    checksum = checksum ^ msg.msg_struct.header;
    checksum = checksum ^ msg.msg_struct.datum1;
    checksum = checksum ^ msg.msg_struct.datum2;
    checksum = checksum ^ msg.msg_struct.datum3;

    return checksum;
}   //end mldChecksum

char* mldMsgToString(char* buff, mld_msg_u msg) {
    /** Convert the hex command code contained in [msg] 
     *  into a string, appending a carriage return
     * 
     *  Command hex codes are 5 bytes long, transmitted as a 
     *  string of hex characters followed by a carriage return.
     * 
     *  Resulting stirng is placed in [buff]. The pointer to [buff]
     *  is also returned.
     *  **/
    
    sprintf(buff,"%0*llX\r",10, msg.msg_hex);   //0-padded, 10-character hex string with carriage return appended (11 total)

    return buff;
}   //end mldMsgToString()

mld_msg_u mldStringToMsg(char* str) {
    mld_msg_u msg;
    msg.msg_hex = strtoll(str,NULL,16);
    return msg;
}   //end mldStringToMsg()

/**
mld_t mldInit(char* sertty, int baud) {
    mld_t mld;
    mld.serial_handle = serOpen(sertty,baud,0);
    
    if (mld.serial_handle < 0) {
        //exit with error if serial connection could not be opened
        printf("CRITICAL Error:\n\t Failed to open serial connection at %s", sertty);
        exit(mld.serial_handle);
    } 
    else {
        //if serial connection opened, see if laser driver is responsive
        mldLinkControl(mld);
    }
}   //end mldInit
**/
/**
int mldClose(mld_t mld){
    int close_status = serClose(mld.serial_handle);
    checkStatus(close_status, "mldClose");
    return close_status
}
**/

/**
int mldSendMsg(mld_t mld, mld_msg_u msg) {
    /** Given an MLD message type union, prepare for serial transmission by:
     *  1) calculating the checksum
     *  2) Converting to string with carriage return appended
     * 
     *  Then transmit via serWrite 

    char out_buff[MSG_BYTES*2];
    msg.msg_struct.checksum = mldChecksum(msg);
    mldMsgToString(out_buff, msg);
    return serWrite(mld.serial_handle,out_buff, MSG_BYTES);
}   //end mldSendMsg
**/
/**
mld_msg_u mldRecvMsg(mld_t mld) {
    /** Read a return message from the MLD driver described  by [mld].
     *  Parse the returned string into a mld_msg_u and return 
    char recv_buff[11];

    int num_bytes = serRead(mld.serial_handle, recv_buff, MSG_BYTES);
    checkStatus(num_bytes, "mldRecvMsg");

    mld_msg_u recv_msg = mldStringToMsg(recv_buff);
    return recv_msg;
}
**/

/**
uint8_t mldLinkControl(mld_t mld) {
    mld_msg_u send_msg;
    mld_msg_u recv_msg;

    send_msg.msg_hex = 0x04000000;                //Link control header = 0x04, rest don't care
    send_msg.msg_struct.checksum = mldChecksum(send_msg);             //calculate checksum
    char checksum = send_msg.msg_struct.checksum; //save checksum to check return

    int send_status = mldSendMsg(mld, send_msg);
    if (send_status < 0) {
        checkStatus(send_status, "mldSendMsg");
    }
    else {
        recv_msg = mldRecvMsg(mld);

    }
}
**/


