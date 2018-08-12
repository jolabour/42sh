#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	unsigned char buf[7];
	int		i;
	read(0, &buf, 6);
	printf("%x, %x, %x, %x", buf[0], buf[1], buf[2], buf[3]);
	return (0);
}
