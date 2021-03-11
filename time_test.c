#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main()
{
    struct timeval now;
    gettimeofday(&now, NULL);

    printf("%ld\t%ld\n",now.tv_sec, now.tv_usec);
    printf("%ld\t%lf\n",now.tv_sec, now.tv_usec / 1000000.0);
    double v = now.tv_sec + now.tv_usec / 1000000.0;
    printf("%f\n", v);

}