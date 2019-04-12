/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:29:11 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:34:04 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_no_such_job(char *job, char *builtin)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	if (builtin)
	{
		ft_putstr_fd(builtin, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(job ? job : "current", STDERR_FILENO);
	ft_putstr_fd(": no such job\n", STDERR_FILENO);
}

void			ft_put_job_title(t_joblist *job, t_42sh *sh, int fd)
{
	ft_putstr_fd("[", fd);
	ft_putnbr_fd(job->num, fd);
	ft_putstr_fd("]", fd);
	ft_putstr_fd(job == sh->current ? "+ " : "  ", fd);
}
