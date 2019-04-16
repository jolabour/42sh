/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:57:16 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/16 07:36:09 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_wait_job(t_joblist *job, int options, t_42sh *shell)
{
	t_proclist	*proc;
	int			status;

	proc = job->process;
	while (proc)
	{
		if (!proc->complete && waitpid(proc->pid, &(proc->status), options))
		{
			if (WIFSTOPPED(proc->status))
				shell->current = job;
			else if (WIFCONTINUED(proc->status))
			{
				proc->status = 0;
				job->stopped = false;
			}
			else
				proc->complete = true;
		}
		status = proc->status;
		proc = proc->next;
	}
	return (status);
}

int				ft_get_retval(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	return (-1);
}

void			ft_manage_status(t_joblist *job, t_42sh *shell)
{
	if (ft_any_interrupted(job))
	{
		if (shell->pgid && g_intr)
		{
			signal(SIGINT, SIG_DFL);
			kill(getpid(), SIGINT);
		}
		if (!shell->pgid)
		{
			shell->stopexe = true;
			ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	if (ft_any_stopped(job))
		job->stopped = true;
	else
		ft_remove_job(job, shell);
}

int				ft_manage_job(t_joblist *job, t_42sh *shell)
{
	int			status;

	status = ft_wait_job(job, shell->pgid ? 0 : WUNTRACED, shell);
	tcgetattr(STDIN_FILENO, &(job->term));
	if (!shell->pgid && shell->foreground)
	{
		tcsetpgrp(STDIN_FILENO, shell->pid);
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(shell->reset_term));
	}
	if (!shell->pgid)
	{
		if (ft_any_stopped(job))
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			ft_report_job_def(job, shell, STDERR_FILENO);
		}
		else if (WIFSIGNALED(status) && WTERMSIG(status) != SIGINT)
		{
			ft_putstr_fd(g_sigtab[WTERMSIG(status) > 0 && WTERMSIG(status)
				< 32 ? WTERMSIG(status) : 0], STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	ft_manage_status(job, shell);
	return (ft_get_retval(status));
}
