#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	unsigned char buf[7];
	int		i;
	i = read(0, &buf, 6);
	printf("%d", i);
	printf("%2x, %2x, %2x, %2x", buf[0], buf[1], buf[2], buf[3]);
	return (0);
}
