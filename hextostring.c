#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

char mldChecksum(long num){
    char checksum = 0x0;
    char mask = 0xFF;

    for (int i = 0; i < 4; i++) {
        checksum = checksum ^ (char)(mask & (num >> (8*i)));
    }
    return checksum;
}

int main(int argc, char* argv[]) {
    char buff[12];
    char hex_str[9];
    long long hex = 0x4FFFF00;
    char checksum = mldChecksum(hex);
    printf("%X\n", hex << 0);
    double aug_num = (hex << 8) & checksum;
    //char buff2[2];
    //sprintf(buff2,"%02X0D",checksum);
    //strcat(buff,buff2);
    //printf("\n");
    //printf(buff);

    return 0;
}