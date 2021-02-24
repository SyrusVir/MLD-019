//#include <pigpio.h>
#include <pigpio_local.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MLD019.h"
#include "MLD019.c"
#include <assert.h>
#include <curses.h>
#include <sys/time.h>

#define SERIAL_TERM "/dev/ttyAMA0" //target PL011 UART module
#define BAUD 9600

typedef enum states {
    WAIT,
    ACTIVE,
    QUIT
} states_t;

void getTimestampedFilePath(char* str_result, size_t str_size) 
{	/**
	Returns to [str_result] the current time (UTC) as a string of format
	YYYY-mm-dd-HH-MM-SS-UUUUUU where mm is the month number and UUUUUU are the microseconds of the epoch time
	**/

	struct timeval curr_time_tv;
		
	//get current time; tv provides sec and usec; tm used for strftime
	gettimeofday(&curr_time_tv, NULL); //get current time in timeval
	struct tm *curr_time_tm = localtime(&(curr_time_tv.tv_sec)); //use sec of timeval to get struct tm

	//use tm to get timestamp string
	strftime(str_result, str_size, "./%Y_%m_%d_%H_%M_%S_%Z_thermal_laser_test.csv",curr_time_tm);	
}

int main(int argc, char** argv) 
{
    gpioInitialise();

    //terminal manipulations for non-blocking getch()
	initscr();
	nodelay(stdscr,true);
	noecho();

    char filepath[200];
    getTimestampedFilePath(filepath,200);

    FILE* f = fopen(filepath, "a");
    fprintf(f, "SEC_ELAPSED, EMITTING, CASE_TEMP (C), LASER_TEMP (C)\n");

    mld_t mld;
    mld.serial_handle = serOpen(SERIAL_TERM, BAUD, 0);

    printf("\"s\" to start\t \"q\" to stop\n\r");
    state_t state = WAIT;

    do {
        char ch;
        ch = getch();

        switch (state) 
        {
            case WAIT:
                if (toUpper(ch) == 'S') {
                    state = ACTIVE;
                }
            break;

            case ACTIVE:
                assert(mldLinkControl(mld) != 0);
                float start_sec = gpioTick() / 1000000.0;
                mldC

            break;
        }
        
    } while (state != QUIT);


    serClose(mld.serial_handle);
    fclose(f);
    gpioTerminate();
    echo();
	endwin(); //restore terminal configuration
    return 0;
}