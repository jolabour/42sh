/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:43:25 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:44:01 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_bg(t_joblist *job, t_42sh *sh)
{
	ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, sh);
	if (!(ft_any_running(job) || ft_any_stopped(job)))
	{
		ft_putstr_fd("42sh: bg: job has terminated\n", STDERR_FILENO);
		sh->retval = 1;
	}
	else
	{
		if (ft_any_stopped(job))
		{
			kill(-job->pgid, SIGCONT);
			ft_put_job_title(job, sh, STDOUT_FILENO);
			ft_putstr_fd(job->cmdline, STDOUT_FILENO);
			ft_putstr_fd(" &\n", STDOUT_FILENO);
			ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, sh);
		}
		else
		{
			ft_putstr_fd("42sh: bg: job ", STDERR_FILENO);
			ft_putnbr_fd(job->num, STDERR_FILENO);
			ft_putstr_fd(" already in background\n", STDERR_FILENO);
		}
	}
}

void			builtin_bg(t_42sh *sh)
{
	t_joblist	*job;

	sh->retval = 0;
	if (sh->pgid)
	{
		ft_putstr_fd("42sh: bg: no job control\n", STDERR_FILENO);
		sh->retval = 1;
	}
	else
	{
		job = NULL;
		if (sh->argv->argv[1] && ft_str_isdigit(sh->argv->argv[1]))
			job = ft_search_job(sh->jobs, ft_atoi(sh->argv->argv[1]));
		else if (!sh->argv->argv[1] || sh->argv->argv[1][0] == '+')
			job = sh->current;
		if (job)
			ft_bg(job, sh);
		else
			ft_no_such_job(sh->argv->argv[1], "bg");
	}
}
