/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:55:42 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:02:41 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_check_job(t_joblist *job, t_42sh *shell)
{
	ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, shell);
	if (!ft_any_running(job))
	{
		if (job->stopped ? !ft_any_stopped(job) : true)
			ft_report_job_def(job, shell, STDERR_FILENO);
		job->stopped = true;
		if (!ft_any_stopped(job))
			ft_remove_job(job, shell);
	}
	else
		job->stopped = false;
}

void			ft_check_jobs(t_42sh *shell)
{
	t_joblist	*jobs;
	t_joblist	*next;

	jobs = shell->jobs;
	while (jobs)
	{
		next = jobs->next;
		ft_check_job(jobs, shell);
		jobs = next;
	}
}
