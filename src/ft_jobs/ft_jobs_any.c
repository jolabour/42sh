/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_any.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:09:44 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:10:12 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_any_stopped(t_joblist *job)
{
	t_proclist	*proc;

	proc = job->process;
	while (proc)
	{
		if (WIFSTOPPED(proc->status))
			return (1);
		proc = proc->next;
	}
	return (0);
}

int				ft_any_running(t_joblist *job)
{
	t_proclist	*proc;

	proc = job->process;
	while (proc)
	{
		if (!(proc->complete || WIFSTOPPED(proc->status)))
			return (1);
		proc = proc->next;
	}
	return (0);
}

int				ft_any_interrupted(t_joblist *job)
{
	t_proclist	*proc;

	proc = job->process;
	while (proc)
	{
		if (WIFSIGNALED(proc->status) && WTERMSIG(proc->status) == SIGINT)
			return (1);
		proc = proc->next;
	}
	return (0);
}
