#include <pigpio_local.h>

#define SHUTTER_PIN 5 
#define ENABLE_PIN 24
#define PULSE_PIN 30

int main() {
    gpioInitialise();
    gpioSetMode(SHUTTER_PIN, PI_OUTPUT);
    gpioSetMode(ENABLE_PIN, PI_OUTPUT);
    gpioSetMode(PULSE_PIN, PI_OUTPUTENABLE_PIN;

    //DISABLE interlocks to allow laser emission
    gpioWrite(SHUTTER_PIN, 1);
    gpioDelay(500*1000);    //sleep 500ms after shutter is disabled
    gpioWrite(ENABLE_PIN, 1);

    gpioTrigger(PULSE_PIN, 2, 1); //2 usec long pulse at PULSE_PIN
    gpioDelay(4);   //4 usec delay
    
    //Enable interlocks to prevent laser emission
    gpioWrite(ENABLE_PIN, 0);
    gpioWrite(SHUTTER_PIN, 0);

    //exit
    gpioTerminate();
}