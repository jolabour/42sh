/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_int_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:37:19 by ttresori          #+#    #+#             */
/*   Updated: 2019/02/18 23:38:10 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fc.h"

static int	get_int_stop_char(t_42sh *sh, char *stop_char, int len_stop)
{
	int			i;
	t_history	*tmp;

	i = 0;
	tmp = sh->history_mark->last;
	while (i < sh->history_mark->size)
	{
		if (ft_strncmp(stop_char, tmp->str, len_stop) == 0)
			return (i);
		tmp = tmp->prev;
		i++;
	}
	return (-1);
}

int			check_if_digit(t_42sh *sh)
{
	if ((ft_isdigit(sh->argv->argv[2][0]) == 1) && sh->argv->argv[3] == NULL)    // -l 1 NULL
	{
		print_delimit_history(sh, ft_atoi(sh->argv->argv[2]),
				sh->history_mark->size);
		return (1);
	}
	else if ((ft_isdigit(sh->argv->argv[2][0]) == 1)   // -l 1 2
			&& (ft_isdigit(sh->argv->argv[3][0]) == 1))
	{
		print_delimit_history(sh, ft_atoi(sh->argv->argv[2]),
				ft_atoi(sh->argv->argv[3]));
		return (1);
	}
	if ((ft_isdigit(sh->argv->argv[2][0]) == 1)   // -l 1 2
			&& (ft_isalpha(sh->argv->argv[3][0]) == 1))
	{
		print_delimit_history(sh, ft_atoi(sh->argv->argv[2]),
				get_int_stop_char(sh, sh->argv->argv[3], ft_strlen(sh->argv->argv[3])));
		return (1);
	}
	return (0);
}

static void	print_delimit_history_str(t_42sh *sh, char *arg_start, char *stop, int start_int, int stop_int)
{
	t_history	*tmp;
	int 		i;
	int			len_start;
	int			len_stop;

	i = 0;
	len_start = -1;
	len_stop = -1;
	tmp = sh->history_mark->last;
	if (arg_start)
		len_start = ft_strlen(arg_start);
	if (stop)
		len_stop = ft_strlen(stop);
	while (i < sh->history_mark->size)
	{
		if (ft_strncmp(arg_start, tmp->str, len_start) == 0)
		{
			if (stop_int != -1)
			{
				print_delimit_history(sh, i, stop_int);
				return ;
			}
			else if (stop_int == -1 && len_stop == -1)
			{
				print_delimit_history(sh, i, sh->history_mark->size);
				return ;
			}
			else if (len_stop > -1)
			{
				if ((len_stop = get_int_stop_char(sh, stop, len_stop)) == -1) // Redefinition on len_start for start in print
				{
					ft_puts_blue("fc: event not found: ");
					ft_putl_green(stop);
					return ;
				}
				print_delimit_history(sh, i, len_stop);
			}
			return ;
		}
		tmp = tmp->prev;
		i++;
	}
	ft_puts_blue("fc: event not found: ");
	ft_putl_green(arg_start);
	(void)start_int;
}

int			check_if_alpha(t_42sh *sh)
{
	if ((ft_isalpha(sh->argv->argv[2][0]) == 1) && sh->argv->argv[3] == NULL)    // -l a  NULL
	{
		print_delimit_history_str(sh, sh->argv->argv[2], NULL, -1, -1);
		return (1);
	}
	if ((ft_isalpha(sh->argv->argv[2][0]) == 1) // -l s a 1
			&& (ft_isdigit(sh->argv->argv[3][0]) == 1))
	{
		print_delimit_history_str(sh, sh->argv->argv[2], NULL, -1, ft_atoi(sh->argv->argv[3]));
		return (1);
	}
	if ((ft_isalpha(sh->argv->argv[2][0]) == 1) // -l s a 1
			&& (ft_isalpha(sh->argv->argv[3][0]) == 1)) // -l a b
	{
		print_delimit_history_str(sh, sh->argv->argv[2], sh->argv->argv[3], -1, -1);
		return (1);
	}
	return (0);
}
