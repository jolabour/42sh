#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	long buf;
	int		i;

	buf = 0;
	i = read(0, &buf, 4);
	printf("%ld", buf);
	return (0);
}
