#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	unsigned char buf;
	int		i;
	read(0, &buf, 1);
	printf("%2x", buf);
	return (0);
}
