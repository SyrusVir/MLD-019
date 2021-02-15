#include "MLD019.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char buff[11];
    char buff1[11];
    mld_msg_u msg;
    msg.msg_num_s = -50;
    /* printf("%lld\n",msg.msg_num_u);
    printf("%llX\n",msg.msg_num_u);
    printf("%lld\n",msg.msg_num_s);
    printf("%llX\n",msg.msg_num_s); */

    snprintf(buff,11,"%0*llX\r",10, msg.msg_num_u);   //0-padded, 10-character hex string with carriage return appended (11 total)
    snprintf(buff1,11,"%0*llX\r",10, msg.msg_num_s & 0xFFFFFFFFFF);   //0-padded, 10-character hex string with carriage return appended (11 total)
    printf("%s\n",buff);
    printf("%s\n",buff1);
    printf("%lld\n",strtoll(buff,NULL,16));
    printf("%llu\n",strtoll(buff1,NULL,16));
    printf("%hhX\n", msg.msg_struct.header);
    printf("%lld\n",mldValidateMsg(msg));
    return 0;
}