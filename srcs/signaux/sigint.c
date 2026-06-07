#include "ft_ping.h"

void	handle_sigint(int sig)
{
	(void)sig;
	print_stats(g_ping);
	close(g_ping->sock);
	exit(0);
}