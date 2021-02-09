#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SERIAL_TERM "/dev/ttyS0" //target PL011 UART module
#define BAUD 9600

void checkStatus(int status, char* error_str) {
    if (status < 0) {
        char str[] = " Error\n";

        char* out_str = (char*) malloc(sizeof(error_str) + sizeof(str) + 1);
        strcpy(out_str,error_str);
        strcat(out_str, str);
        printf(out_str);
        free(out_str);
        exit(status);
    }
    else {
        printf("%s status: %d\n", error_str, status);
    }
}
int main() {
    checkStatus(gpioInitialise(), "gpioInitialise");

    int serial_handle = serOpen(SERIAL_TERM, BAUD, 0);
    checkStatus(serial_handle, "serOpen");

    char out_data[] = "Hello World!\n\r";
    char in_data[sizeof(out_data)];
    checkStatus(serWrite(serial_handle, out_data, sizeof(out_data)),"serWrite");
    
    while(!serDataAvailable(serial_handle)) {};
    int num = 0;
    while (num < sizeof(out_data)) {
        printf("%d %s\n", num, in_data);
        num += serRead(serial_handle,in_data+num,sizeof(out_data) - num);
    }
    printf("%s\n", in_data);
    serClose(serial_handle);
    gpioTerminate();
    return 0;
}