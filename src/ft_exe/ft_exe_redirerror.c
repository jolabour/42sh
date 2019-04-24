/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_redirerror.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:30:41 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/24 15:26:01 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// typedef enum	e_error_file
// {
// 	NO_ERR_FILE = 0,
// 	ERR_FILE_ACCESS = 1,
// 	ERR_FILE_LOOP = 1 << 1,
// 	ERR_FILE_NOTDIR = 1 << 2,
// 	ERR_FILE_NAMETOOLONG = 1 << 3,
// 	ERR_FILE_NOENT = 1 << 4,
// 	ERR_FILE_UNKNOWN = 1 << 5
// }				t_error_file;

// int				ft_check_path(char *path, char *current, struct stat *sstat,
// 				int symlinks)
// {
// 	char		*tmp;
// 	char		first[_XOPEN_PATH_MAX];
// 	char		link_path[_XOPEN_PATH_MAX];
// 	int			ret;

// 	if (symlinks > _POSIX_SYMLINK_MAX)
// 		return (ERR_FILE_LOOP);
// 	tmp = ft_strchr(current, '/');
// 	if (ft_strlen(path) >= _XOPEN_PATH_MAX
// 		|| (tmp ? tmp - current : ft_strlen(current)) >= _XOPEN_NAME_MAX)
// 		return (ERR_FILE_NAMETOOLONG);
// 	first = ft_strncpy(first, path, tmp ? tmp - path + 1 : _XOPEN_PATH_MAX);
// 	if (lstat(first, sstat))
// 		return (access(first, F_OK) ? ERR_FILE_NOENT : ERR_FILE_UNKNOWN);
// 	if (S_ISLNK(sstat->st_mode))
// 	{
// 		ft_strncpy(link_path, path, current - path);
// 		if ((ret = readlink(first, link_path + (current - path),
// 			_XOPEN_PATH_MAX - (current - path) - 1)) == -1)
// 			return (ERR_FILE_UNKNOWN);
// 		if ((current - path) + ret + (tmp ? ft_strlen(tmp) : 0)
// 			>= _XOPEN_PATH_MAX)
// 			return (ERR_FILE_NAMETOOLONG);
// 		ft_strcpy(link_path + (current - path) + ret, tmp);
// 		return (ft_check_path(link_path, link_path + (current - path) + ret, sstat, symlinks + 1));
// 	}
// 	if (tmp)
// 	{
// 		if (!S_ISDIR(sstat->st_mode))
// 			return (ERR_FILE_NOTDIR);
// 		if (!access(first, X_OK))
// 			return (ERR_FILE_ACCESS);
// 		while (
// 	}
// }

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
