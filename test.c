#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("pid: %d pgid: %d\n", getpid(), getpgrp());
}
