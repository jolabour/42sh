/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_redirerror.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:30:41 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/25 04:50:34 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_open_error(char *path, int options, char *unexp)
{
	int			fd;
	struct stat	sstat;

	if ((fd = open(path, options)) == -1)
	{
		ft_putstr_fd("42sh: ", STDERR_FILENO);
		ft_putstr_fd(unexp, STDERR_FILENO);
		if (access(path, F_OK))
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else if (lstat(path, &sstat))
			ft_putstr_fd(": Unknown error (lstat)\n", STDERR_FILENO);
		else if (S_ISDIR(sstat.st_mode))
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		else if ((((options & O_RDONLY) || (options & O_RDWR))
			&& access(path, R_OK)) || (((options & O_WRONLY)
			|| (options & O_RDWR)) && access(path, W_OK)))
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Unknown error. For more informations please feel "
				"free to make a request at errno@missing.42.fr\n",
				STDERR_FILENO);
		free(path);
	}
	return (fd);
}

int				ft_ambigous_error(char *fd, char *unexp)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(unexp, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	free(fd);
	return (1);
}

int				ft_badfd_error(char *fd, char *unexp)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(unexp, STDERR_FILENO);
	ft_putstr_fd(": Bad file descriptor\n", STDERR_FILENO);
	free(fd);
	return (1);
}
