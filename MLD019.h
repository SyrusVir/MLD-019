#ifndef _MLD019_H_
#define _MLD019_H

#include <pigpio.h>
#include <stdint-gcc.h>
#include <stdbool.h>

typedef enum mld_mode {
    MLD_MODE_HARDWARE,
    MLD_MODE_SOFTWARE
} mld_mode_t;

typedef struct MldDriver {
    mld_mode_t mode;
    int serial_handle;

} mld_t;

typedef struct MldMessage {
    uint8_t checksum;  //LSB
    uint8_t datum3;
    uint8_t datum2;
    uint8_t datum1;
    uint8_t header;    //MSB
} mld_msg_t;

typedef union MldMessageUnion
{
    mld_msg_t msg_struct;
    char msg_arr[5];    //msg_arr[0] = LSB
    uint64_t msg_num_u: 40;
    int64_t msg_num_s: 40;
} mld_msg_u;

//prints [status]. Prints [error_str] if [status] < 0
void checkStatus(int status, char* error_str);
void printMsgStruct(mld_msg_u msg);
int mldSendMsg(mld_t mld, mld_msg_u msg);
mld_msg_u mldRecvMsg(mld_t mld);

//Calculates checksum as XOR of upper 4-bytes of [msg]
char mldChecksum(mld_msg_u msg);

//Checks msg for any errors. Returns 0 if none occured
int64_t mldValidateMsg(mld_msg_u msg);

//Converting messages to hexadecimal string
char* mldMsgToString(char* buff, mld_msg_u msg); 

//convert hexadecimal string into a message
mld_msg_u mldStringToMsg(char* str);

//Utility function that sends a message containing [hex_cmd], returning the response.
mld_msg_u mldExecuteCMD(mld_t mld, uint64_t hex_cmd);

int64_t mldLinkControl(mld_t mld);
/**
mldReadRTC

mldCaseTemp

mldVLD

mldStatus

mldBoardTemp

mldDigitalInputMonitor

mldSerialNum

mldHWSWMode

mldCheckConfig

mldTrigSource

mldSetInterlock

mldSetEnable

mldSetPRR
**/
#endif