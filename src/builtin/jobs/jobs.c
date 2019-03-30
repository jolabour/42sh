/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 12:26:36 by geargenc          #+#    #+#             */
/*   Updated: 2019/03/30 20:27:43 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

typedef struct	s_opt
{
	char		**argv;
	char		**after_opts;
	bool		available[256];
	bool		set[256];
}				t_opt;

void		ft_init_opts(t_opt *opt, char *available)
{
	ft_bzero(opt, sizeof(t_opt));
	while (available)
	{
		opt->available[*available] = true;
		available++;
	}
}

int			ft_bad_opt(char *head, char opt)
{
	ft_putstr_fd(head, 2);
	ft_putstr_fd(": -", 2);
	ft_putchar_fd(opt, 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (-1);
}

int			ft_get_opts(t_opt *opt, char **argv, char *error)
{
	int		i;

	opt->argv = argv;
	opt->after_opts = argv;
	while ((*(opt->after_opts))[0] == '-')
	{
		if (ft_strequ(*(opt->after_opts), "--"))
		{
			opt->after_opts++;
			return (0);
		}
		i = 1;
		while ((*(opt->after_opts))[i])
		{
			if (opt->available[(*(opt->after_opts))[i]])
				opt->set[(*(opt->after_opts[i]))] = true;
			else
				return (ft_bad_opt(error, (*(opt->after_opts))[i]));
			i++;
		}
		opt->after_opts++;
	}
	return (0);
}

t_joblist		*ft_search_job(t_joblist *list, int num)
{
	while (list)
	{
		if (list->num == num)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void			ft_no_such_job(char *job)
{
	ft_putstr_fd("42sh: jobs: ", 2);
	ft_putstr_fd(job, 2);
	ft_putstr_fd(": no such job\n", 2);
}

void			ft_jobs(t_opt *opt, t_42sh *sh)
{
	t_joblist	*jobs;

	if (!(*(opt->after_opts)))
	{
		jobs = sh->jobs;
		while (jobs)
			ft_report_job(opt, jobs, sh);
	}
	else while ((*(opt->after_opts)))
	{
		jobs = NULL;
		if ((*(opt->after_opts))[0] == '+')
			jobs = sh->current;
		else if (ft_str_isdigit((*(opt->after_opts))))
			jobs = ft_search_job(sh->jobs, ft_atoi((*(opt->after_opts))));
		if (jobs == NULL)
		{
			ft_no_such_job((*(opt->after_opts)));
			sh->retval = 1;
		}
		else
			ft_report_job(opt, jobs, sh);
		opt->after_opts++;
	}
}

void		builtin_jobs(t_42sh *sh)
{
	t_opt	opt;

	sh->retval = 0;
	ft_init_opts(&opt, "lp");
	if (ft_get_opts(&opt, sh->argv->argv, "42sh: jobs"))
	{
		ft_putstr_fd("jobs: usage: jobs [-lp] [jobspec ...]\n", 2);
		sh->retval = 2;
	}
	else
		ft_jobs(&opt, sh);
}