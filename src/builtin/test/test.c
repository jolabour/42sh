#include "sh.h"

const char			option_tab[OPTION_TEST] = {'b', 'c', 'd', 'e', 'f', 'g', 'L', 'p', 'r', 'S', 's', 'u', 'w', 'x', 'z'};

const t_test			action_option[OPTION_TEST] = {test_b, test_c, test_d, test_e, test_f, test_g, test_L, test_p, test_r, test_S, test_s, test_u, test_w, test_x, test_z};

int			execute_test(t_42sh *sh, char c)
{
	int		i;
	struct stat info;

	i = 0;
	while (i < OPTION_TEST)
	{
		if (option_tab[i] == c)
		{
			if (stat(sh->argv->argv[2], &info) != 0 && sh->argv->argv[1][2] != 'z')
			{
				sh->retval = 1;
				return (0);
			}
			if (sh->argv->size > 3)
			{
				ft_putendl_fd("test: too many arguments", 2);
				sh->retval = 2;
				return (0);
			}
			action_option[i](sh, info);
			return (1);
		}
		i++;
	}
	ft_putstr_fd("test: Unknown condition: ", 2);
	ft_putendl_fd(sh->argv->argv[1], 2);
	sh->retval = 2;
	return (0);
}

int			check_option(t_42sh *sh)
{
	if (sh->argv->argv[1][0] != '-' && sh->argv->size == 3)
	{
		ft_putstr_fd("42sh: parse error: condition expected: ", 2);
		ft_putendl_fd(sh->argv->argv[1], 2);
		sh->retval = 2;
		return (1);
	}
	if (sh->argv->argv[1][0] == '-' && sh->argv->size == 3)
	{
			execute_test(sh, sh->argv->argv[1][1]);
			return (1);
	}
	return (0);
}

void		builtin_test(t_42sh *sh)
{
	if (sh->argv->size == 1)
		sh->retval = 1;
	else if (sh->argv->size == 2)
		sh->retval = 0;
	else if (check_option(sh) > 0)
	{
		ft_putnbr(sh->retval);
		return ;
	}
	else if (sh->argv->size == 4)
		execute_other_opt(sh, sh->argv->argv[2]);
	else
		sh->retval = 2;
	ft_putnbr(sh->retval);
}
