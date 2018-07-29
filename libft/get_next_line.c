/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 17:39:12 by abeauvoi          #+#    #+#             */
/*   Updated: 2018/04/12 01:53:16 by abeauvoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"

/*
** This get_next_line returs the length of the line instead of one.
*/

static int			build_one_line(int fd, char *buf, t_file *file)
{
	int		n;
	char	*tmp;

	tmp = NULL;
	while ((n = read(fd, buf, BUFF_SIZE)))
	{
		if (!(tmp = ft_strnew(file->saved_len + n)))
			return (-1);
		ft_memcpy(tmp, file->saved, file->saved_len);
		ft_memcpy(tmp + file->saved_len, buf, n);
		free(file->saved);
		file->saved = tmp;
		file->saved_len += n;
		if ((tmp = ft_memchr(buf, DELIM, n)) != NULL)
			break ;
	}
	return (tmp != NULL ? file->saved_len - n + (tmp - buf) : file->saved_len);
}

static t_file		*get_current_file(t_hist *hist, const int fd)
{
	t_file			*file;

	if (!hist->files)
	{
		if (!(hist->files = (t_file *)malloc(sizeof(t_file))))
			return (NULL);
		ft_bzero(hist->files, sizeof(t_file));
		hist->files->fd = fd;
		return (hist->files);
	}
	file = hist->files;
	while (file->fd != fd && file->next != NULL)
		file = file->next;
	if (file->fd == fd)
		return (file);
	if (!(file->next = (t_file *)malloc(sizeof(*file))))
		return (NULL);
	ft_bzero(file->next, sizeof(t_file));
	file->next->fd = fd;
	return (file->next);
}

static size_t		clear_history(t_hist *hist, t_file *file, size_t len_line,
		bool reached_eof)
{
	char			*tmp;
	t_file			*prev;

	if ((file->saved_len -= len_line) > 0)
		--file->saved_len;
	tmp = (!file->saved_len ? NULL : ft_memcpy(ft_strnew(file->saved_len),
				file->saved + len_line + 1, file->saved_len));
	free(file->saved);
	file->saved = tmp;
	if (reached_eof)
	{
		if ((prev = hist->files) == file)
			hist->files = hist->files->next;
		else
			while (prev->next != file)
				prev = prev->next;
		prev->next = file->next;
		free(file);
		return (0);
	}
	return (len_line);
}

static int			get_one_line(t_hist *hist, t_file *file, char **line,
		size_t len_line)
{
	if (file->saved != NULL)
	{
		if (!(*line = ft_memcpy(ft_strnew(len_line), file->saved, len_line)))
			return (-1);
	}
	return (clear_history(hist, file, len_line,
				(file->saved == NULL && len_line == 0 ? 1 : 0)));
}

int					get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_hist	hist = {NULL};
	t_file			*file;
	int				n;
	char			*add_nl;

	if (fd == -1 || !line || read(fd, buf, 0) == -1)
		return (-1);
	buf[BUFF_SIZE] = 0;
	if (!(file = get_current_file(&hist, fd)))
		return (-1);
	if (file->saved != NULL
			&& (add_nl = ft_memchr(file->saved, DELIM, file->saved_len)))
		return (get_one_line(&hist, file, line, add_nl - file->saved));
	n = build_one_line(fd, buf, file);
	if (n < 0)
		return (-1);
	return (get_one_line(&hist, file, line, n));
}
