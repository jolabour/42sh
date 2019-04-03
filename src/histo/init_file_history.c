/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 04:04:26 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/03 04:14:05 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_put_space_fd(int nb, int fd)
{
	while (nb > 0)
	{
		ft_putchar_fd(' ', fd);
		nb--;
	}
}

void	spacing_fd(int line, int fd)
{
	if (line < 10)
	{
		ft_put_space_fd(4, fd);
		return ;
	}
	if (line < 100)
	{
		ft_put_space_fd(3, fd);
		return ;
	}
	else
		ft_put_space_fd(2, fd);
}

void	init_history(t_42sh *sh, char *path)
{
	char	*line;
	int		fd;

	sh->history_mark = (t_history_mark*)ft_malloc_exit(sizeof(t_history_mark));
	sh->history_mark->begin = NULL;
	sh->history_mark->last = NULL;
	sh->history_mark->cur = NULL;
	sh->history_mark->size = 0;
	sh->history_mark->pos = 0;
	sh->history_mark->error_code = 0;
	if (access(path, F_OK) == 0)
	{
		fd = open(path, O_RDWR);
		while (get_next_line(fd, &line) != 0)
		{
			add_to_list(sh, line);
			free(line);
		}
		close(fd);
	}
	else
	{
		fd = open(path, O_CREAT);
		close(fd);
	}
}

void	add_history(t_42sh *sh, char *line, char *path)
{
	int fd;

	if (line[0] == '\n')
		return ;
	add_to_list(sh, line);
	fd = open(path, O_CREAT | O_RDWR);
	lseek(fd, 0, SEEK_END);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\0", fd);
	close(fd);
}
