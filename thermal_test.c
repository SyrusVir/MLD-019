//#include <pigpio.h>
#include <pigpio_local.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MLD019.h"
#include <assert.h>
#include <curses.h>
#include <sys/time.h>

#define SERIAL_TERM "/dev/ttyAMA0" //target PL011 UART module
#define BAUD 9600

#define ENABLE_PIN 6 //physical pin 31
#define PULSE_PIN 26 //physical pin 37

typedef enum states {
    WARMUP,
    LASE,
    COOL,
    WAIT,
    QUIT
} states_t;

char [8][3]

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

float getEpochTime()
{
    int sec;
    int usec;

    gpoTime(&sec, &usec);

    return (float) sec + (usec / 1000000.0);
} //end getEpochTime()

int writeTemps(mld_t mld, int f)
{

} //end writeTemps()

int main(int argc, char** argv) 
{
    if (argc != 4)
    {
        printf("ARGUMENT ERROR\n");
        printf("\tUsage: sudo ./%s.c [warm-up seconds] [lasing seconds] [cool down seconds]\n");
        return -1;
    }

    int warmup_sec = atoi(argv[1]);
    int lasing_sec = atoi(argv[2]);
    int cool_sec = atoi(argv[3]);

    gpioInitialise();
    gpioSetMode(ENABLE_PIN, PI_OUTPUT);
    gpioWrite(ENABLE_PIN, 0); //write low to prevent emission

    //terminal manipulations for non-blocking getch()
	initscr();
	nodelay(stdscr,true);
	noecho();

    char filepath[200];
    getTimestampedFilePath(filepath,200);

    FILE* f = fopen(filepath, "a");
    fprintf(f, "MSEC_ELAPSED, STATE, BOARD_TEMP (C), LASER_TEMP (C)\n");

    mld_t mld;
    mld.serial_handle = serOpen(SERIAL_TERM, BAUD, 0);

    //verify driver comms
    if (mldLinkControl(mld) != 0) {
        //terminate if error communicating with driver
        print("ERROR with driver communications\n");
        return -1;
    }
    
    char c;
    state = WAIT;
    do
    {
        printf("Enter \'S\' to start...\n\r");
        scanf("%c", &c);
    } while (c != 'S');


    float start_time = getEpcohTime();
    float warmup_end_time = start_time + warmup_sec;
    float lase_end_time = warmup_end_time + lasing_sec;
    float cool_end_time = lase_end_time + cool_sec;
    float curr_time;
    while (getch() != ' ' && getch() != 'q')
    {
        curr_time = getEpochTime(); 
        if (curr_time < warmup_end_time) {}
        else if (warm_end_time < curr_time && curr_time < lase_end_time)
        {
            if (state != LASE)
            {
                gpioSetMode(PULSE_PIN, PI_OUTPUT);
                gpioWrite(PULSE_PIN, 0);
                gpioWrite(ENABLE_PIN,1);
                gpioSetPWMfrequency(PULSE_PIN,1000);
                gpioPWM(PULSE_PIN,255/2);
                state = LASE;
            }
        }
        else if (lase_end_time < curr_time && curr_time < cool_end_time)
        {
            if (state != _CRT_OBSOLETE)
            {
                gpioPWM(PULSE_PIN,0);
                gpioWrite(ENABLE_PIN,0);
                state = COOL;
            }
        }

        float board_temp = mldBoardTemp(mld);
        float laser_temp = mldCaseTemp(mld);

        fprintf(f, "%.2f,%.2f,%.2f\n", curr_time,board_temp, laser_temp);

        gpioDelay(100000); //delay 100 ms
    }

q
    gpioPWM(0);
    gpioWrite(ENABLE_PIN,0);
    serClose(mld.serial_handle);
    fclose(f);
    gpioTerminate();
    echo();
	endwin(); //restore terminal configuration
    return 0;
}