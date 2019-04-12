/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:00:10 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 10:03:54 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_exe_rpar(t_node *current, t_42sh *shell)
{
	t_joblist	*job;

	if (!shell->forked)
	{
		if (!(job = ft_get_job(current, shell)))
			exit(2);
		ft_launch_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, job->pgid);
		shell->retval = ft_manage_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, shell->pid);
		return (shell->retval);
	}
	signal(SIGINT, &ft_handler);
	if (current->redir
		&& g_exetab[current->redir->token](current->redir, shell))
		exit(1);
	exit(g_exetab[current->right->token](current->right, shell));
}

int				ft_exe_rbrace(t_node *current, t_42sh *shell)
{
	t_tmpfd		*tmp;
	int			ret;

	shell->forked = 0;
	ret = 0;
	if (current->redir)
		ret = g_exetab[current->redir->token](current->redir, shell);
	tmp = shell->tmp_fds;
	shell->tmp_fds = NULL;
	if (!ret)
		ret = g_exetab[current->right->token](current->right, shell);
	ft_reset_tmp_fd(tmp);
	return (shell->retval = ret);
}
