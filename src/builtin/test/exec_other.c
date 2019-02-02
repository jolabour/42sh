#include "sh.h"

const char			*option_tab_other[7] = {"=", "!=", "-eq", "-ne", "-ge", "-lt", "-le"};

const t_ak			action_option_other[7] = {test_equal, test_diff, test_eq, test_ne, test_ge, test_lt, test_le};

int			check_nbr(t_42sh *sh)
{
	int		i;

	i = 0;
	if (sh->argv->argv[1][i] == '-' || sh->argv->argv[1][i] == '+')
		i++;
	while (sh->argv->argv[1][i])
	{
		if (sh->argv->argv[1][i] > '9' || sh->argv->argv[1][i] < '0')
			return (1);
		i++;
	}
	i = 0;
	if (sh->argv->argv[3][i] == '-' || sh->argv->argv[3][i] == '+')
		i++;
	while (sh->argv->argv[3][i])
	{
		if (sh->argv->argv[3][i] > '9' || sh->argv->argv[3][i] < '0')
			return (3);
		i++;
	}
	return (0);
}

int			execute_other_opt(t_42sh *sh, char *str)
{
	int		i;
	int		pos;

	i = 0;
	while (i < 7)
	{
		if (ft_strequ(str, option_tab_other[i]) != 0)
		{
			if (i >= 2 && (pos = check_nbr(sh)) != 0)
			{
				sh->argv->error_code = 2;
				ft_putstr("test: integer expression expected: ");
				ft_putendl(sh->argv->argv[pos]);
				return (2);
			}
			action_option_other[i](sh);
			return (1);
		}
		i++;
	}
	ft_putstr("42sh: condition expected: ");
	ft_putendl(sh->argv->argv[2]);
	return (0);
}
