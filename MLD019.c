#include <MLD019.h>
#include <stdio.h>

#define SERIAL_TTY "/dev/ttyAMA0"
#define BAUD 9600

int mldConfig(char* sertty, unsigned int baud) {
    int h = serOpen(sertty, baud, 0);
    return h; 
}


void checkStatus(int status, char* error_str) {
    if (status < 0) {
        
        char str[] = " Error %d\n";

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
    checkStatus(gpioInitialise(), "gpioInitialise()");

    int h = serOpen(SERIAL_TTY, BAUD,0);

}