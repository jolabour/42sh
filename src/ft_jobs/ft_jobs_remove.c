/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:00:29 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/26 05:51:37 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_joblist		*ft_get_last_job(t_joblist *jobs)
{
	if (jobs)
		while (jobs->next)
			jobs = jobs->next;
	return (jobs);
}

void			ft_remove_proc(t_proclist *proc)
{
	int			i;

	free(proc->cmdline);
	if (proc->path)
		free(proc->path);
	if (proc->args)
	{
		i = 0;
		while (proc->args[i])
		{
			free(proc->args[i]);
			i++;
		}
		free(proc->args);
	}
	free(proc);
}

void			ft_remove_job(t_joblist *job, t_42sh *shell)
{
	t_joblist	**tmp_job;
	t_proclist	*tmp_proc;

	tmp_job = &(shell->jobs);
	while (*tmp_job)
	{
		if (*tmp_job == job)
			*tmp_job = (*tmp_job)->next;
		else
			tmp_job = &((*tmp_job)->next);
	}
	if (job == shell->current)
		shell->current = ft_get_last_job(shell->jobs);
	while (job->process)
	{
		tmp_proc = job->process;
		job->process = job->process->next;
		ft_remove_proc(tmp_proc);
	}
	free(job->cmdline);
	free(job);
}
