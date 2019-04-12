/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 12:26:36 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:43:19 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_jobs(t_opt *opt, t_42sh *sh)
{
	t_joblist	*jobs;

	if (!(*(opt->after_opts)))
		ft_report_all_jobs(opt, sh);
	else
		while ((*(opt->after_opts)))
		{
			jobs = NULL;
			if ((*(opt->after_opts))[0] == '+')
				jobs = sh->current;
			else if (ft_str_isdigit((*(opt->after_opts))))
				jobs = ft_search_job(sh->jobs, ft_atoi((*(opt->after_opts))));
			if (jobs == NULL)
			{
				ft_no_such_job((*(opt->after_opts)), "jobs");
				sh->retval = 1;
			}
			else
				ft_report_job(opt, jobs, sh);
			opt->after_opts++;
		}
}

void			builtin_jobs(t_42sh *sh)
{
	t_opt		opt;

	sh->retval = 0;
	ft_init_opts(&opt, "lp");
	if (ft_get_opts(&opt, sh->argv->argv + 1, "42sh: jobs"))
	{
		ft_putstr_fd("jobs: usage: jobs [-lp] [jobspec ...]\n", STDERR_FILENO);
		sh->retval = 2;
	}
	else
		ft_jobs(&opt, sh);
}
