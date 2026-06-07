#include "ft_ping.h"

void	print_help(void)
{
	printf("Usage\n  ft_ping [options] <destination>\n\n");
	printf("Options:\n");
	printf("  <destination>\t\tnom DNS ou adresse IP\n");
	printf("  -h, -?\t\tAfficher cette aide et quitter\n");
	printf("  -v\t\t\tMode verbeux (affiche les paquets ignorés)\n");
	exit(0);
}

void	print_stats(t_ping *ping)
{
	double	loss = 0.0;
	double	avg;
	struct timeval	now;
	long			elapsed_ms;
 
	gettimeofday(&now, NULL);
	elapsed_ms = (now.tv_sec - ping->start_time.tv_sec) * 1000 + (now.tv_usec - ping->start_time.tv_usec) / 1000;
	if (ping->sent > 0)
		loss = 100.0 * (ping->sent - ping->received) / ping->sent;
	printf("\n--- %s ping statistics ---\n", ping->host);
	printf("%d packets transmitted, %d received, %.0f%% packet loss, time %ldms\n", ping->sent, ping->received, loss, elapsed_ms);
	if (ping->received > 0)
	{
		avg = ping->rtt_sum / ping->received;
		printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", ping->rtt_min, avg, ping->rtt_max, compute_mdev(ping));
	}
}

void	print_stats_sigquit(t_ping *ping)
{
	double	loss = 0.0;
	double	avg = 0.0;
 
	if (ping->sent > 0)
		loss = 100.0 * (ping->sent - ping->received) / ping->sent;
	if (ping->received > 0)
		avg = ping->rtt_sum / ping->received;
	printf("\b\b%d/%d packets, %.0f%% loss",
		ping->received, ping->sent, loss);
	if (ping->received > 0)
		printf(", min/avg/ewma/max = %.3f/%.3f/%.3f/%.3f ms",
			ping->rtt_min, avg, ping->rtt_ewma, ping->rtt_max);
	printf("\n");
}