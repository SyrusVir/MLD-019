#include "MLD019.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char buff[10];
    //char buff1[11];
    mld_msg_u msg;
    msg.msg_num_s = 0x04FFFF0000;
    msg.msg_struct.checksum = mldChecksum(msg);
    printMsgStruct(msg);
    mldMsgToString(buff,msg);
    printf("%s\n",buff);
    for (int i=0; i< 11; i++) {
        printf("%X ",buff[i]);
    }

    char buff1[11] = {'a','a','b','b','c','c','e','e','d','d'};
    mld_msg_u msg2 = mldStringToMsg(buff1);
    printf("\n%llX\n",msg2.msg_num_u);

    
    return 0;
}