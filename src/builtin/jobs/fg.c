/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:42:55 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:43:11 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_fg(t_joblist *job, t_42sh *sh)
{
	ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, sh);
	if (!(ft_any_running(job) || ft_any_stopped(job)))
	{
		ft_putstr_fd("42sh: fg: job has terminated\n", STDERR_FILENO);
		sh->retval = 1;
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(job->term));
		tcsetpgrp(STDIN_FILENO, job->pgid);
		if (ft_any_stopped(job))
			kill(-job->pgid, SIGCONT);
		ft_putstr_fd(job->cmdline, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		job->stopped = false;
		sh->retval = ft_manage_job(job, sh);
	}
}

void			builtin_fg(t_42sh *sh)
{
	t_joblist	*job;

	if (sh->pgid)
	{
		ft_putstr_fd("42sh: fg: no job control\n", STDERR_FILENO);
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
			ft_fg(job, sh);
		else
			ft_no_such_job(sh->argv->argv[1], "fg");
	}
}
