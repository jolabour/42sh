/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_report.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:22:58 by geargenc          #+#    #+#             */
/*   Updated: 2020/03/18 19:13:30 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_report_job_long(t_joblist *job, t_42sh *sh, int fd)
{
	t_proclist	*proc;

	proc = job->process;
	while (proc)
	{
		proc == job->process ? ft_put_job_title(job, sh, fd)
			: ft_putstr_fd("     ", fd);
		ft_putnbr_fd(proc->pid, fd);
		ft_putstr_fd(" ", fd);
		if (!(ft_exited(proc, fd) || ft_signaled(proc->status, fd)
			|| ft_stopped_long(proc->status, fd)))
			ft_running(proc->status, fd);
		ft_putstr_fd(proc == job->process ? "  " : "| ", fd);
		ft_putstr_fd(proc->cmdline, fd);
		ft_putstr_fd("\n", fd);
		proc = proc->next;
	}
}

void			ft_report_job_pgid(t_joblist *job, t_42sh *sh, int fd)
{
	(void)sh;
	ft_putnbr_fd(job->pgid, fd);
	ft_putstr_fd("\n", fd);
}

void			ft_report_job_def(t_joblist *job, t_42sh *sh, int fd)
{
	t_proclist	*last;

	last = job->process;
	if (last)
		while (last->next)
			last = last->next;
	ft_put_job_title(job, sh, fd);
	if (ft_any_running(job))
		ft_running(0, fd);
	else if (!ft_stopped(last->status, fd))
	{
		if (ft_any_stopped(job))
			ft_stopped(_WSTOPPED, fd);
		else if (!(ft_exited(last, fd)
			|| ft_signaled(last->status, fd)))
			write(fd, "                              ", 30);
	}
	ft_putstr_fd(job->cmdline, fd);
	ft_putstr_fd("\n", fd);
}

void			ft_report_job(t_opt *opt, t_joblist *job, t_42sh *sh)
{
	ft_wait_job(job, WUNTRACED | WNOHANG | WCONTINUED, sh);
	if (opt && opt->set['l'])
		ft_report_job_long(job, sh, STDOUT_FILENO);
	else if (opt && opt->set['p'])
		ft_report_job_pgid(job, sh, STDOUT_FILENO);
	else
		ft_report_job_def(job, sh, STDOUT_FILENO);
}

void			ft_report_all_jobs(t_opt *opt, t_42sh *sh)
{
	t_joblist	*jobs;
	t_joblist	*next;

	jobs = sh->jobs;
	while (jobs)
	{
		next = jobs->next;
		ft_report_job(opt, jobs, sh);
		if (!(ft_any_running(jobs) || ft_any_stopped(jobs)))
			ft_remove_job(jobs, sh);
		jobs = next;
	}
}
