#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>

int main(int argc, char* argv[]) {
    uint64_t num = 0;
    if (argc > 1) {
        num = atoll(argv[1]);
    }
    printf("num=%lld\n", num);
    
    //num to hex
    char buff[12];
    sprintf(buff,"%0*llX\r",11,num);
    printf("buff=%s",buff);
    printf("converted=%lld\n",strtoll(buff,NULL,16));
}