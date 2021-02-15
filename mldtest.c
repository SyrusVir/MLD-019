#include "MLD019.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char buff[11];
    char buff1[11];
    mld_msg_u msg;
    msg.msg_num_s = 0xAABBCCDDEE;

    uint16_t temp =  (msg.msg_struct.datum2 | msg.msg_struct.datum1 << 8);
    temp = (msg.msg_num_u & 0x00FFFF0000) >> 16;
    printf("%hhX %hhX\n", msg.msg_struct.datum1, msg.msg_struct.datum2);
    printf("%X\n",temp);
    return 0;
}