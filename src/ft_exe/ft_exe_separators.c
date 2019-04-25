/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_separators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:04:27 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/25 04:48:22 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_exe_pipe(t_node *current, t_42sh *shell)
{
	t_joblist	*job;

	shell->forked = 0;
	job = ft_get_job(current, shell);
	ft_launch_job(job, shell);
	if (!shell->pgid && shell->foreground)
		tcsetpgrp(STDIN_FILENO, job->pgid);
	return (shell->retval = ft_manage_job(job, shell));
}

int				ft_exe_and(t_node *current, t_42sh *shell)
{
	t_joblist	*job;
	int			foreground;

	if (shell->pgid)
		return (ft_exe_semi(current, shell));
	shell->forked = 0;
	job = ft_get_job(current->left, shell);
	foreground = shell->foreground;
	shell->foreground = 0;
	ft_launch_job(job, shell);
	shell->foreground = foreground;
	if (!(shell->pgid))
		ft_print_bg(job, shell);
	shell->retval = 0;
	if (current->right)
		shell->retval = g_exetab[current->right->token](current->right, shell);
	return (shell->retval);
}

int				ft_exe_semi(t_node *current, t_42sh *shell)
{
	int			ret;

	if (current->right)
		shell->forked = 0;
	if ((ret = g_exetab[current->left->token](current->left, shell)) < 0)
		return (ret);
	if (current->right && !shell->stopexe)
		ret = g_exetab[current->right->token](current->right, shell);
	return (ret);
}

int				ft_exe_and_if(t_node *current, t_42sh *shell)
{
	int			ret;

	shell->forked = 0;
	if ((ret = g_exetab[current->left->token](current->left, shell)))
		return (ret);
	if (!shell->stopexe)
		ret = g_exetab[current->right->token](current->right, shell);
	return (ret);
}

int				ft_exe_or_if(t_node *current, t_42sh *shell)
{
	int			ret;

	shell->forked = 0;
	if ((ret = g_exetab[current->left->token](current->left, shell)) < 1)
		return (ret);
	if (!shell->stopexe)
		ret = g_exetab[current->right->token](current->right, shell);
	return (ret);
}
