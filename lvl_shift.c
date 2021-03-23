#include <pigpio.h>
#include <stdio.h>

#define OUT_PIN 4 //physical pin 7

int main()
{
    uint8_t mode = 0;
    gpioInitialise();

    gpioSetMode(OUT_PIN, PI_OUTPUT);

    gpioWrite(OUT_PIN, mode);

    while(1)
    {
        char c;
        scanf("%c%*c", &c);
        if (c == 'q') break;
        mode = !mode;
        printf("mode = %d\n", mode);
        gpioWrite(OUT_PIN, mode);

    }

    gpioWrite(OUT_PIN, mode);
    gpioTerminate();
    
    return 0;
    
}