#include "ft_ping.h"

void	handle_sigquit(int sig)
{
	(void)sig;
	print_stats_sigquit(g_ping);
}