#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <math.h>
#include <errno.h>
#include <time.h>

typedef struct s_ping
{
	char				*host;
	char				ip_str[INET_ADDRSTRLEN];
	int					sock;
	struct sockaddr_in	addr;
	
	pid_t				pid;
	
	unsigned short		seq;
	unsigned short		id;
	
	double				rtt_min;
	double				rtt_max;
	double				rtt_sum;
	double				rtt_sum_sq;
	double				rtt_ewma;
	
	struct timeval		start_time;

	int					sent;
	int					received;
	
	int					flag_verbose;
	int					flag_help;
}	t_ping;

extern t_ping *g_ping;

void	print_stats_sigquit(t_ping *ping);
void	print_stats(t_ping *ping);
void	print_help(void);

unsigned short	checksum(void *data, int len);
double	compute_mdev(t_ping *ping);

void	init_ping(t_ping *ping);

void	handle_sigint(int sig);
void	handle_sigquit(int sig);

void	check_args(t_ping *ping, char **av);

void	sleep_interruptible(void);
double	timeval_diff_ms(struct timeval *start, struct timeval *end);