/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_tmpfd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:15:14 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 09:15:56 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_dup_tmp_fd(int fd)
{
	int			cpy;
	bool		denied[3];

	denied[STDIN_FILENO] = false;
	denied[STDOUT_FILENO] = false;
	denied[STDERR_FILENO] = false;
	while ((cpy = ft_dup_exit(fd)) >= STDIN_FILENO && cpy <= STDERR_FILENO)
		denied[cpy] = true;
	if (denied[STDIN_FILENO])
		close(STDIN_FILENO);
	if (denied[STDOUT_FILENO])
		close(STDOUT_FILENO);
	if (denied[STDERR_FILENO])
		close(STDERR_FILENO);
	return (cpy);
}

void			ft_build_tmp_fd(int fd, t_tmpfd **begin)
{
	t_tmpfd		*tmp;

	tmp = (t_tmpfd *)ft_malloc_exit(sizeof(t_tmpfd));
	tmp->initial = fd;
	if ((tmp->cloexec = fcntl(fd, F_GETFD)) != -1)
	{
		tmp->tmp = ft_dup_tmp_fd(fd);
		fcntl(tmp->tmp, F_SETFD, FD_CLOEXEC);
	}
	else
		tmp->tmp = -1;
	tmp->next = *begin;
	*begin = tmp;
}

void			ft_reset_tmp_fd(t_tmpfd *begin)
{
	t_tmpfd		*tmp;

	while (begin)
	{
		if (begin->tmp == -1)
			close(begin->initial);
		else
		{
			if (dup2(begin->tmp, begin->initial) == -1)
				exit(2);
			close(begin->tmp);
			fcntl(begin->initial, F_SETFD, begin->cloexec);
		}
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
}
