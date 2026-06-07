#include "ft_ping.h"

static void	is_valid_flag(t_ping *ping, const char *av)
{
	int	i = 1;

	while (av[i])
	{
		if (av[i] != 'v' && av[i] != '?' && av[i] != 'h')
		{
			fprintf(stderr, "ft_ping: option invalide -- '%c'\n", av[i]);
			exit(EXIT_FAILURE);
		}
		if (av[i] == 'v')
			ping->flag_verbose = 1;
		if (av[i] == 'h' || av[i] == '?')
			ping->flag_help = 1;
		i++;
	}
}

void	check_args(t_ping *ping, char **av)
{
	int	i = 1;
	int	host_found = 0;

	while (av[i])
	{
		if (av[i][0] == '-')
			is_valid_flag(ping, av[i]);
		else
		{
			if (host_found)
			{
				fprintf(stderr, "ft_ping: hôte en double\n");
				exit(EXIT_FAILURE);
			}
			ping->host = av[i];
			host_found = 1;
		}
		i++;
	}
	if (!host_found && !ping->flag_help)
	{
		fprintf(stderr, "ft_ping: hôte manquant\n");
		exit(EXIT_FAILURE);
	}
}