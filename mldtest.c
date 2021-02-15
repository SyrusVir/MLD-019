#include "MLD019.h"
#include <stdio.h>

int main() {

    mld_msg_u msg;
    msg.msg_num = -146;
    printf("%llu\n", mldValidateMsg(msg));
    return 0;
}