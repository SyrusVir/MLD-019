#include <pigpio.h>

#define SHUTTER_PIN 29 
#define ENABLE_PIN 31
#define PULSE_PIN 33

int main() {
    gpioInitialise();
    gpioSetMode(SHUTTER_PIN, PI_OUTPUT);
    gpioSetMode(ENABLE_PIN, PI_OUTPUT);
    gpioSetMode(PULSE_PIN, PI_OUTPUT);

    //DISABLE interlocks to allow laser emission
    // gpioWrite(SHUTTER_PIN, 1);
    // gpioDelay(500*1000);    //sleep 500ms after shutter is disabled
    // gpioWrite(ENABLE_PIN, 1);

    // gpioTrigger(PULSE_PIN, 2, 1); //2 usec long pulse at PULSE_PIN
    // gpioDelay(4);   //4 usec delay
    
    //Enable interlocks to prevent laser emission
    gpioWrite(ENABLE_PIN, 0);
    gpioDelay(1000000);
    gpioWrite(SHUTTER_PIN, 0);

    //exit
    gpioTerminate();
}