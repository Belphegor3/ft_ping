#include "ft_ping.h"

unsigned short	checksum(void *data, int len)
{
	unsigned short	*ptr;
	unsigned int	sum = 0;

	ptr = data;
	while (len > 1)
	{
		sum += *ptr++;
		len -= 2;
	}
	if (len == 1)
		sum += *(unsigned char *)ptr;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return ((unsigned short)~sum);
}