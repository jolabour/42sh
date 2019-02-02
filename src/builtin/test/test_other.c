#include "sh.h"

void		test_equal(t_42sh *sh)
{
	if (ft_strequ(sh->argv->argv[1], sh->argv->argv[3]) == 1)
		sh->argv->error_code = 0;
	else
		sh->argv->error_code = 1;
}

void		test_diff(t_42sh *sh)
{
	if (ft_strequ(sh->argv->argv[1], sh->argv->argv[3]) == 1)
		sh->argv->error_code = 1;
	else
		sh->argv->error_code = 0;
}

void		test_eq(t_42sh *sh)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[1]);
	tmp2 = ft_atoi(sh->argv->argv[3]);
	if (tmp == tmp2)
		sh->argv->error_code = 0;
	else
		sh->argv->error_code = 1;
}

void		test_ne(t_42sh *sh)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[1]);
	tmp2 = ft_atoi(sh->argv->argv[3]);
	if (tmp != tmp2)
		sh->argv->error_code = 0;
	else
		sh->argv->error_code = 1;
}

void		test_ge(t_42sh *sh)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[1]);
	tmp2 = ft_atoi(sh->argv->argv[3]);
	if (tmp >= tmp2)
		sh->argv->error_code = 0;
	else
		sh->argv->error_code = 1;
}

void		test_lt(t_42sh *sh)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[1]);
	tmp2 = ft_atoi(sh->argv->argv[3]);
	if (tmp < tmp2)
		sh->argv->error_code = 0;
	else
		sh->argv->error_code = 1;
}

void		test_le(t_42sh *sh)
{
	int		tmp;
	int		tmp2;

	tmp = ft_atoi(sh->argv->argv[1]);
	tmp2 = ft_atoi(sh->argv->argv[3]);
	if (tmp <= tmp2)
		sh->argv->error_code = 0;
	else
		sh->argv->error_code = 1;
}
