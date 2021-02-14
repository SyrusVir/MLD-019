#include <stdio.h>
#include <stdlib.h>

typedef struct MldMessage {
    char checksum;
    char datum3;
    char datum2;
    char datum1;
    char header;
} mld_msg_t;

typedef union MldMessageUnion
{
    mld_msg_t msg_struct;
    char msg_arr[5];
    long long msg_hex: 40;
} mld_msg_u;
mld_msg_u mldChecksum(mld_msg_u msg){
    /**Parameteres: mld_msg_u msg - an MLD019 message union representation
     * Return:      mld_msg_u msg - same union with checksum calculated)
     * **/

    char checksum = 0x0;
    for (int i = 1; i < 5; i++) {
        checksum = checksum ^ msg.msg_arr[i];
    }
    msg.msg_struct.checksum = checksum;
    return msg;
}
int main() {
    //initializing using struct
    mld_msg_u msg;
    msg.msg_struct.header = 0x04;
    msg.msg_struct.datum1 = 0xFF;
    msg.msg_struct.datum2 = 0xFF;
    msg.msg_struct.datum3 = 0x00;
    //msg.msg_struct.checksum = 0x04;
    msg = mldChecksum(msg);
    printf("%010llX\n", msg.msg_hex);
    
    
    //using string to hex
    char hex_str[] = "04FFFF0004\r";
    mld_msg_u msg1;
    msg1.msg_hex = strtoll(hex_str,NULL,16);
    printf("%hhX\n", msg.msg_struct.checksum);
    printf("%hhX\n", msg.msg_struct.datum3);
    printf("%hhX\n", msg.msg_struct.datum2);
    printf("%hhX\n", msg.msg_struct.datum1);
    printf("%hhX\n", msg.msg_struct.header);


    for (int i = 0; i < 5; i++) {
        printf("%hhX ", msg.msg_arr[i]);
    }
    return 0;
}