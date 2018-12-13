/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:03:05 by ttresori          #+#    #+#             */
/*   Updated: 2018/12/13 01:10:56 by ttresori         ###   ########.fr       */
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

void	up_history(t_42sh *sh)
{
	static int line = 0;
	int 	fd;
	int 	i;
	char	**split;
	char	last_line[256];
	char	*get_line;

	i = 0;
	fd = open(sh->path_history, O_CREAT, ~O_RDWR);
	//lseek(fd, SEEK_SET, 0);
	while (get_next_line(fd, &get_line) == 1)
	{
		ft_strcpy(last_line, get_line);
		i++;
		free(get_line);
		if (i == line - 1)
			break ;
	}
	line = i;
	split = ft_strsplitset(last_line, " ");
//	ft_putstr(split[1]);
	free(sh->stdin->input);
	sh->stdin->input = ft_strdup(split[1]);
	ft_free_split(split);
}

static int check_if_valid(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' || line[i] != '\t' || line[i] != '\n')
			return (0);
		i++;
	}
	return (-1);
}

void	add_history(char *line, char *path)
{
	int fd;
	int	nb_line;
	char	*get_line;

	nb_line = 0;
	if (check_if_valid(line) == -1)
		return ;
	if (line[0] == ' ' || line[0] == '\n')
		return ;
	fd = open(path, O_CREAT, ~O_RDWR);
	lseek(fd, SEEK_SET, 0);
	while (get_next_line(fd, &get_line) == 1)
	{
		nb_line++;
		free(get_line);
	}
	close(fd);
	fd = open(path, O_APPEND | O_RDWR);
	spacing_fd(nb_line, fd);
	ft_putnbr_fd(nb_line++, fd);
	ft_putstr_fd("  ", fd);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\0", fd);
	close(fd);
}
