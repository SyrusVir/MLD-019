#include <stdio.h>
#include <stdlib.h>
#include "MLD019.h"

int64_t cast(uint64_t num){
    return num;
}

int main() {
    //initializing using struct
    mld_msg_u msg;
    uint64_t hex_num = 0xFFFFF38c10;
    printf("u=%llu\n", hex_num);
    printf("u=%lld\n", hex_num);
    printf("d=%llu\n", cast(hex_num));
    printf("d=%lld\n", cast(hex_num));
    msg.msg_num = cast(hex_num);
    for (int i = 0; i < 5; i++) {
        printf("%hhX ", msg.msg_arr[i]);
    }

    printf("\n");
    printf("%hhX ", msg.msg_struct.header);
    printf("%hhX ", msg.msg_struct.datum1);
    printf("%hhX ", msg.msg_struct.datum2);
    printf("%hhX ", msg.msg_struct.datum3);
    printf("%hhX ", msg.msg_struct.checksum);
    printf("\n");

    return 0;
}