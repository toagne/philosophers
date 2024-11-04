#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long    get_time()
{
    struct timeval      time;
    long                res;

    gettimeofday(&time, NULL);
    res = time.tv_sec * 1000000 + time.tv_usec;
    return (res);
}

void    precise_usleep(long sleep)
{
    long current_time;
    long elapsed;
    long rem;

    current_time = get_time();
    printf("initial time = %ld\n", current_time);
    while (get_time() - current_time < sleep)
    {
        elapsed = get_time() - current_time;
        //printf("elapsed = %lu\n", elapsed);
        rem = sleep - elapsed;
        //printf("rem = %lu\n", rem);
        if (rem > 10000)
            usleep(5000);
        else if (rem > 1000)
            usleep(rem / 2);
        else
            while (get_time() - current_time < sleep)
                ;
      }
}

void    new_precise_usleep(long sleep)
{
    long current_time;

    current_time = get_time();
    while (get_time() - current_time < sleep)
    {
        usleep(500);
    } 
}

void    refined_precise_usleep(long sleep)
{
    long	current_time;
    struct timeval  start;
    struct timeval  end;
	long	real_time;

	current_time = get_time();
	while (get_time() - current_time < sleep)
	{
		gettimeofday(&start, NULL);
		usleep(500);
		gettimeofday(&end, NULL);
		real_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        //printf("real sleep time 1:      %ld microseconds\n", real_time);
		if (real_time > 500)
        {
            //gettimeofday(&start, NULL);
            usleep(500 - (real_time - 500));
            //gettimeofday(&end, NULL);
		    //real_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
            //printf("real sleep time 2:      %ld microseconds\n", real_time);
        }
    }
}

int main()
{
    struct timeval  start;
    struct timeval  end;
    long            time;
    long            real_time;

    time = 60 * 1000;
    gettimeofday(&start, NULL);
    usleep(time);
    gettimeofday(&end, NULL);
    real_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    printf("requested sleep time: %ld microseconds\n", time);
    printf("real sleep time:      %ld microseconds\n", real_time);

    /*gettimeofday(&start, NULL);
    precise_usleep(time);
    gettimeofday(&end, NULL);
    real_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    //printf("requested sleep time: %ld microseconds\n", time);
    //printf("real sleep time:      %ld microseconds\n", real_time);

    gettimeofday(&start, NULL);
    new_precise_usleep(time);
    gettimeofday(&end, NULL);
    real_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    //printf("requested sleep time: %ld microseconds\n", time);
    //printf("real sleep time:      %ld microseconds\n", real_time);*/

    gettimeofday(&start, NULL);
    refined_precise_usleep(time);
    gettimeofday(&end, NULL);
    real_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    printf("requested sleep time: %ld microseconds\n", time);
    printf("real sleep time:      %ld microseconds\n", real_time);
}