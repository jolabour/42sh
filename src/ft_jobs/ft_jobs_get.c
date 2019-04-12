/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:48:17 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 10:48:23 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_proclist		*ft_get_pipeline(t_node *current)
{
	t_proclist	*process;

	process = (t_proclist *)ft_malloc_exit(sizeof(t_proclist));
	*process = (t_proclist){0, NULL, NULL, 0, false, NULL, NULL, NULL};
	if (current->token == PIPE)
	{
		process->command = current->left;
		process->cmdline = g_cmdlinetab[current->left->token](current->left);
		process->next = ft_get_pipeline(current->right);
	}
	else
	{
		process->command = current;
		process->cmdline = g_cmdlinetab[current->token](current);
		process->next = NULL;
	}
	return (process);
}

int				ft_get_job_number(t_joblist *jobs)
{
	int			max;

	max = 0;
	while (jobs)
	{
		if (jobs->num > max)
			max = jobs->num;
		jobs = jobs->next;
	}
	return (max + 1);
}

void			ft_push_job_back(t_joblist *job, t_42sh *shell)
{
	t_joblist	**tmp;

	tmp = &(shell->jobs);
	while (*tmp)
		tmp = &((*tmp)->next);
	*tmp = job;
}

t_joblist		*ft_get_job(t_node *current, t_42sh *shell)
{
	t_joblist	*job;

	job = (t_joblist *)ft_malloc_exit(sizeof(t_joblist));
	job->process = ft_get_pipeline(current);
	if (shell->pgid)
		job->pgid = shell->pgid;
	else
		job->pgid = 0;
	job->cmdline = g_cmdlinetab[current->token](current);
	job->next = NULL;
	job->num = ft_get_job_number(shell->jobs);
	job->stopped = false;
	tcgetattr(STDIN_FILENO, &(job->term));
	if (!shell->current)
		shell->current = job;
	ft_push_job_back(job, shell);
	return (job);
}
