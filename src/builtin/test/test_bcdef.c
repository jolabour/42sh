#include "sh.h"

void		test_b(t_42sh *sh, struct stat info)
{
	if ((S_ISBLK(info.st_mode)) == 1)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_c(t_42sh *sh, struct stat info)
{
	if ((S_ISCHR(info.st_mode)) == 1)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_d(t_42sh *sh, struct stat info)
{
	if ((S_ISDIR(info.st_mode)) == 1)
		sh->retval = 0;
	else
		sh->retval = 1;
}

void		test_e(t_42sh *sh, struct stat info)
{
	(void)info;
	sh->retval = 0;
}

void		test_f(t_42sh *sh, struct stat info)
{
	if ((S_ISREG(info.st_mode)) == 1)
		sh->retval = 0;
	else
		sh->retval = 1;
}
