/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_opts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:08:11 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:08:31 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_init_opts(t_opt *opt, char *available)
{
	ft_bzero(opt, sizeof(t_opt));
	while (*available)
	{
		opt->available[(int)*available] = true;
		available++;
	}
}

int			ft_bad_opt(char *head, char opt)
{
	ft_putstr_fd(head, STDERR_FILENO);
	ft_putstr_fd(": -", STDERR_FILENO);
	ft_putchar_fd(opt, STDERR_FILENO);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	return (-1);
}

int			ft_get_opts(t_opt *opt, char **argv, char *error)
{
	int		i;

	opt->argv = argv;
	opt->after_opts = argv;
	while (*(opt->after_opts) && (*(opt->after_opts))[0] == '-'
		&& (*(opt->after_opts))[1])
	{
		if (ft_strequ(*(opt->after_opts), "--"))
		{
			opt->after_opts++;
			return (0);
		}
		i = 1;
		while ((*(opt->after_opts))[i])
		{
			if (opt->available[(int)(*(opt->after_opts))[i]])
				opt->set[(int)(*(opt->after_opts))[i]] = true;
			else
				return (ft_bad_opt(error, (*(opt->after_opts))[i]));
			i++;
		}
		opt->after_opts++;
	}
	return (0);
}
