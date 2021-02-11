#include <stdio.h>
#include <stdlib.h>

char mldChecksum(long num){
    char checksum = 0x0;
    char mask = 0xFF;

    for (int i = 0; i < 4; i++) {
        checksum = checksum ^ (char)(mask & (num >> (8*i)));
    }
    return checksum;
}

int main(int argc, char* argv[]) {
    char* buff = (char*) malloc(11*sizeof(char));
    char hex_str[9];
    long long  hex = 0x4FFFF00;
    char checksum = mldChecksum(hex);
    printf("%llX\n", hex << 16);
    printf("%X\n", checksum);
    long long aug_num = (hex << 8) | (checksum);
    printf("%llX\n", aug_num);
    sprintf(buff,"%0*llX\r",5*2,aug_num);
    //buff[10] = '\r';    

    printf(buff);
    printf("\n");
    for (int i = 0; i < 11; i++) {
        printf("%X\n",*(buff+i));
    }
    return 0;
}