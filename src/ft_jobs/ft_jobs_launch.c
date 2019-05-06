/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:53:45 by geargenc          #+#    #+#             */
/*   Updated: 2019/05/06 19:58:56 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_launch_process(t_proclist *proc, t_42sh *shell,
				int pipefd[3], pid_t pgid)
{
	shell->jobs = NULL;
	setpgid(getpid(), (pgid = pgid ? pgid : getpid()));
	if (!shell->pgid && shell->foreground)
		tcsetpgrp(STDIN_FILENO, pgid);
	if (!shell->pgid)
		ft_reset_signals();
	shell->pgid = pgid;
	if (pipefd[2] != -1 && pipefd[2] != STDIN_FILENO
		&& ft_dup2_exit(pipefd[2], STDIN_FILENO))
		close(pipefd[2]);
	if (pipefd[1] != -1 && pipefd[1] != STDOUT_FILENO
		&& ft_dup2_exit(pipefd[1], STDOUT_FILENO))
		close(pipefd[1]);
	close(pipefd[0]);
	shell->forked = 1;
	if (proc->path)
		ft_exe_file(proc->command, shell, proc->path, proc->args);
	exit(g_exetab[proc->command->token](proc->command, shell));
}

void			ft_launch_job(t_joblist *job, t_42sh *shell)
{
	t_proclist	*proc;
	int			pipefd[3];

	proc = job->process;
	ft_memset(pipefd, -1, sizeof(pipefd));
	while (proc)
	{
		if (proc->next)
			ft_pipe_exit(pipefd);
		else
			pipefd[1] = -1;
		proc->pid = ft_fork_exit();
		if (!proc->pid)
			ft_launch_process(proc, shell, pipefd, job->pgid);
		if (job->pgid == 0)
			job->pgid = proc->pid;
		if (!shell->foreground)
			shell->last_bg = proc->pid;
		setpgid(proc->pid, job->pgid);
		close(pipefd[1]);
		close(pipefd[2]);
		pipefd[2] = pipefd[0];
		proc = proc->next;
	}
}
