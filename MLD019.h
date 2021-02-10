#include <pigpio.h>

typedef enum mld_mode {
    MLD_HARDWARE,
    MLD_SOFTWARE
} mld_mode_t;

typedef struct MldDriver {
    mld_mode_t mode;
    int serial_handle;

} mld_driver_t;

int mldSend
int mldRead

mldLinkControl

mldReadRTC

mldCaseTemp

mldVLD

mldStatus

mldBoardTemp

mldDigitalInputMonitor

mldSerialNum

mldHWSWMode

mldCheckConfig

mldTrigSource

mldSetInterlock

mldSetEnable

mldSetPRR

