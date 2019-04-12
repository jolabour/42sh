/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:11:39 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 09:13:01 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_execve_exit(char *path, char **argv, char **envp)
{
	execve(path, argv, envp);
	ft_putstr_fd("42sh: execve: Error\n", STDERR_FILENO);
	exit(2);
}

int			ft_pipe_exit(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("42sh: pipe: Error\n", 2);
		exit(2);
	}
	return (0);
}

pid_t		ft_fork_exit(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("42sh: fork: Error\n", 2);
		exit(2);
	}
	return (pid);
}

int			ft_dup_exit(int fd)
{
	int		ret;

	if (fcntl(fd, F_GETFD) == -1)
		return (-1);
	if ((ret = dup(fd)) == -1)
	{
		ft_putstr_fd("42sh: dup: Error\n", 2);
		exit(2);
	}
	return (ret);
}

int			ft_dup2_exit(int fd1, int fd2)
{
	int		ret;

	if (fcntl(fd1, F_GETFD) == -1)
		return (-1);
	if ((ret = dup2(fd1, fd2)) == -1)
	{
		ft_putstr_fd("42sh: dup: Error\n", 2);
		exit(2);
	}
	return (ret);
}
