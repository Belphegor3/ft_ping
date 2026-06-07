#include "ft_ping.h"

static void	init_host(t_ping *ping)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr_in	*addr;
	int					status;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	status = getaddrinfo(ping->host, NULL, &hints, &res);
	if (status != 0)
	{
		fprintf(stderr, "ft_ping: %s: %s\n", ping->host, gai_strerror(status));
		exit(EXIT_FAILURE);
	}
	addr = (struct sockaddr_in *)res->ai_addr;
	memset(&ping->addr, 0, sizeof(struct sockaddr_in));
	ping->addr.sin_family = AF_INET;
	ping->addr.sin_addr = addr->sin_addr;
	inet_ntop(AF_INET, &addr->sin_addr, ping->ip_str, INET_ADDRSTRLEN);
	freeaddrinfo(res);
}

static int	init_icmp_socket(void)
{
	int				sock;
	int				ttl = 64;
	struct timeval	tv = {1, 0};

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock < 0)
	{
		perror("socket error");
		exit(EXIT_FAILURE);
	}
	setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	return (sock);
}

void	init_ping(t_ping *ping)
{
	ping->id = (unsigned short)getpid();
	init_host(ping);
	ping->sock = init_icmp_socket();
}