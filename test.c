#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	long	buf;
	int		i;
	i = 0;
	buf = 0;
	read(0, &buf, 2);
	printf("%ld", buf);
	return (0);
}
