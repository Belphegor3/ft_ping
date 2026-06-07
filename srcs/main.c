#include "ft_ping.h"

t_ping *g_ping;

int	build_icmp_packet(t_ping *p, char *buffer)
{
	struct icmphdr	*icmp;
	int				packet_size;

	packet_size = sizeof(struct icmphdr) + 56;
	memset(buffer, 0, packet_size);
	icmp = (struct icmphdr *)buffer;
	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->un.echo.id = p->id;
	icmp->un.echo.sequence = ++p->seq;
	icmp->checksum = 0;
	icmp->checksum = checksum(buffer, packet_size);
	return (packet_size);
}

int	receive_icmp_reply(t_ping *p, char *buffer, struct timeval *start)
{
	struct sockaddr_in	addr;
	socklen_t			addr_len;
	ssize_t				bytes;
	struct timeval		end;
	struct iphdr		*ip_hdr;
	struct icmphdr		*icmp_hdr;
	int					ip_header_len;
	double				rtt;

	addr_len = sizeof(addr);
	bytes = recvfrom(p->sock, buffer, 1024, 0,
			(struct sockaddr *)&addr, &addr_len);
	gettimeofday(&end, NULL);
	if (bytes < 0)
	{
		if (p->flag_verbose)
			perror("recvfrom error");
		return (-1);
	}
	ip_hdr = (struct iphdr *)buffer;
	ip_header_len = ip_hdr->ihl * 4;
	icmp_hdr = (struct icmphdr *)(buffer + ip_header_len);
	if (icmp_hdr->type != ICMP_ECHOREPLY)
	{
		if (p->flag_verbose)
			printf("[verbose] paquet ICMP ignoré (type=%d code=%d)\n",
				icmp_hdr->type, icmp_hdr->code);
		return (-1);
	}
	if (icmp_hdr->un.echo.id != p->id)
		return (-1);
	rtt = timeval_diff_ms(start, &end);
	p->received++;
	if (p->received == 1 || rtt < p->rtt_min)
		p->rtt_min = rtt;
	if (rtt > p->rtt_max)
		p->rtt_max = rtt;
	p->rtt_sum += rtt;
	p->rtt_sum_sq += rtt * rtt;
	if (p->received == 1)
		p->rtt_ewma = rtt;
	else
		p->rtt_ewma += (rtt - p->rtt_ewma) / 8.0;
	printf("%zd bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
		bytes - ip_header_len,
		inet_ntoa(addr.sin_addr),
		icmp_hdr->un.echo.sequence,
		ip_hdr->ttl,
		rtt);
	return (0);
}

void	ping_loop(t_ping *ping)
{
	char			send_buf[64];
	char			recv_buf[1024];
	struct timeval	start;
	int				packet_size;

	printf("PING %s (%s): 56 data bytes\n", ping->host, ping->ip_str);
	gettimeofday(&ping->start_time, NULL);
	while (1)
	{
		packet_size = build_icmp_packet(ping, send_buf);
		gettimeofday(&start, NULL);
		if (sendto(ping->sock, send_buf, packet_size, 0,
				(struct sockaddr *)&ping->addr,
				sizeof(ping->addr)) < 0)
		{
			perror("sendto error");
			ping->sent++;
			// sleep(1);
			sleep_interruptible();
			continue ;
		}
		ping->sent++;
		receive_icmp_reply(ping, recv_buf, &start);
		// sleep(1);
		sleep_interruptible();
	}
}

int	main(int ac, char **av)
{
	t_ping	ping;

	if (getuid() != 0)
	{
		printf("\x1b[5;31mft_ping a besoin des droits d utilisateur root\x1b[0m\n");
		return EXIT_FAILURE;
	}
	if (ac == 1)
	{
		fprintf(stderr, "destination manquante\n");
		fprintf(stderr, "Essayez: ft_ping -h\n");
		return (EXIT_FAILURE);
	}
	memset(&ping, 0, sizeof(t_ping));
	check_args(&ping, av);
	if (ping.flag_help)
		print_help();
	init_ping(&ping);
	g_ping = &ping;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	ping_loop(&ping);
	close(ping.sock);
	return (0);
}