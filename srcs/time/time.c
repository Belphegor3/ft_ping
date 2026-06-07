#include "ft_ping.h"

double	timeval_diff_ms(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) * 1000.0
		+ (end->tv_usec - start->tv_usec) / 1000.0);
}

void	sleep_interruptible(void)
{
	struct timespec	time_to_sleep;
	struct timespec	remaining;
 
	time_to_sleep.tv_sec = 1;
	time_to_sleep.tv_nsec = 0;
	while (nanosleep(&time_to_sleep, &remaining) == -1 && errno == EINTR)
		time_to_sleep = remaining;
}