#include "ft_ping.h"

double	compute_mdev(t_ping *ping)
{
	double	avg;
	double	avg_sq;
	double	variance;
 
	if (ping->received == 0)
		return (0.0);
	avg = ping->rtt_sum / ping->received;
	avg_sq = ping->rtt_sum_sq / ping->received;
	variance = avg_sq - (avg * avg);
	if (variance < 0.0)
		variance = 0.0;
	return (sqrt(variance));
}