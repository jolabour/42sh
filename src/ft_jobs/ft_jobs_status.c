/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:11:56 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:15:46 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_exited(t_proclist *proc, int fd)
{
	int			spaces;

	if (proc->complete && WIFEXITED(proc->status))
	{
		ft_putstr_fd("Done", fd);
		spaces = 26;
		if (WEXITSTATUS(proc->status))
		{
			ft_putstr_fd("(", fd);
			ft_putnbr(WEXITSTATUS(proc->status));
			ft_putstr_fd(")", fd);
			spaces = 26 - ft_chars_in_int(WEXITSTATUS(proc->status)) - 2;
		}
		if (spaces > 0 && spaces < 27)
			write(fd, "                          ", (size_t)spaces);
		return (1);
	}
	return (0);
}

int				ft_signaled(int status, int fd)
{
	int			sig;

	if (WIFSIGNALED(status))
	{
		sig = (WTERMSIG(status) > 0 && WTERMSIG(status) < 32)
			? WTERMSIG(status) : 0;
		ft_putstr_fd(g_sigtab[sig], fd);
		write(fd, "                              ",
			30 - ft_strlen(g_sigtab[sig]));
		return (1);
	}
	return (0);
}

int				ft_stopped_long(int status, int fd)
{
	int			sig;

	if (WIFSTOPPED(status))
	{
		sig = (WSTOPSIG(status) > 0 && WSTOPSIG(status) < 32)
			? WSTOPSIG(status) : 0;
		ft_putstr_fd(g_sigtab[sig], fd);
		write(fd, "                              ",
			30 - ft_strlen(g_sigtab[sig]));
		return (1);
	}
	return (0);
}

int				ft_stopped(int status, int fd)
{
	int			spaces;

	if (WIFSTOPPED(status))
	{
		ft_putstr_fd("Stopped", fd);
		spaces = 23;
		if (WSTOPSIG(status) > 0 && WSTOPSIG(status) < 32)
		{
			ft_putstr_fd("(", fd);
			ft_putstr_fd(g_sigabrevtab[WSTOPSIG(status)], fd);
			ft_putstr_fd(")", fd);
			spaces = 23 - ft_strlen(g_sigabrevtab[WSTOPSIG(status)]) - 2;
		}
		if (spaces > 0 && spaces < 24)
			write(fd, "                       ", spaces);
		return (1);
	}
	return (0);
}

int				ft_running(int status, int fd)
{
	(void)status;
	ft_putstr_fd("Running                       ", fd);
	return (1);
}
