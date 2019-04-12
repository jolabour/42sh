/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:27:22 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 10:28:43 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_exe_file_error(char *path, char *error)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
}

int				ft_exe_file_check(char *path)
{
	struct stat	info;

	if (!ft_strchr(path, '/'))
	{
		ft_exe_file_error(path, ": command not found\n");
		return (127);
	}
	if (stat(path, &info))
	{
		ft_exe_file_error(path, ": no such file or directory\n");
		return (127);
	}
	if ((S_ISDIR(info.st_mode)) == 1)
	{
		ft_exe_file_error(path, ": is a directory\n");
		return (126);
	}
	if (access(path, X_OK) == -1 || ((S_ISREG(info.st_mode)) != 1))
	{
		ft_exe_file_error(path, ": Permission denied\n");
		return (126);
	}
	return (0);
}

int				ft_exe_file(t_node *current, t_42sh *shell,
				char *path, char **args)
{
	t_joblist	*job;

	if (!shell->forked)
	{
		job = ft_get_job(current, shell);
		job->process->path = path;
		job->process->args = args;
		shell->argv->argv = NULL;
		ft_launch_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, job->pgid);
		shell->retval = ft_manage_job(job, shell);
		if (!shell->pgid && shell->foreground)
			tcsetpgrp(STDIN_FILENO, shell->pid);
		return (shell->retval);
	}
	if (current->redir
		&& g_exetab[current->redir->token](current->redir, shell))
		exit(1);
	if (!path)
		exit(0);
	if (!(shell->retval = ft_exe_file_check(path)))
		ft_execve_exit(path, args, shell->copy_env);
	exit(shell->retval);
}
