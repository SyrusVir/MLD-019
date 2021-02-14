#include "MLD019.c"

int main() {

    mld_msg_u msg;
    char buff[11]; //(char*) malloc(sizeof(char)*11);
    msg.msg_hex = 0xABE3881109; //for long inputs, only the lower 5 bytes are used in union
    msg.msg_struct.checksum = mldChecksum(msg);
    printf("%hhX\n", msg.msg_struct.header);
    printf("%hhX\n", msg.msg_struct.datum1);
    printf("%hhX\n", msg.msg_struct.datum2);
    printf("%hhX\n", msg.msg_struct.datum3);
    printf("%hhX\n", msg.msg_struct.checksum);

    printf("msg_arr=");
    for (int i = 0; i < 5; i++) {
        printf("%hhX ", msg.msg_arr[i]);
    }
    printf("\n");
    mldMsgToString(buff, msg);
    printf("msg_str=%s\n", buff);
    printf("sizeof(buff)=%d\n", sizeof(buff));
    printf("msg chars:\n");
    for (int i = 0; i < 11; i++) {
        printf("%hhX ", buff[i]);
    }
    printf("\n");

    mld_msg_u recv_msg = mldStringToMsg("A4FFFF0004\r");

    printf("recv_msg=%llX\n",recv_msg.msg_hex);
    printf("recv_msg.checksum=%hhX\n",mldChecksum(recv_msg));
    return 0;
}