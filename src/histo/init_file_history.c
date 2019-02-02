/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:03:05 by ttresori          #+#    #+#             */
/*   Updated: 2019/01/25 20:31:03 by ttresori         ###   ########.fr       */
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

/*static int check_if_valid(char *line)
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
*/

void		del_history(t_history_mark *history)
{
	t_history	*tmp;

	while (history->size > 0)
	{
		tmp = history->begin;
		history->begin = history->begin->next;
		if (history->begin == NULL)
			history->last = NULL;
		else
			history->begin->prev = NULL;
		ft_strdel(&tmp->str);
		free(tmp);
		history->size--;
	}
	free(history);
	/*t_history *tmp;
	t_history *prev;

	tmp = *history;
	while (tmp)
	{
		free(tmp->str);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}*/
}

void		print_history(t_history_mark *history_mark)
{
	t_history	*tmp;

	tmp = history_mark->begin;
	while (tmp)
	{
		ft_putendl(tmp->str);
		tmp = tmp->next;
	}
}

t_history *new_history(char *line)
{
	t_history *new;

	if (!(new = malloc(sizeof(t_history))))
		print_error(_ENOMEM, 1);
	new->str = ft_strdup(line);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_to_list(t_42sh *sh, char *line)
{
	t_history *new;

	new = new_history(line);
	if (sh->history_mark->size == 0)
	{
		new->next = sh->history_mark->last;
		new->prev = sh->history_mark->begin;
		sh->history_mark->begin = new;
		sh->history_mark->last = new;
	}
	else
	{
		new->prev = NULL;
		new->next = sh->history_mark->begin;
		sh->history_mark->begin->prev = new;
		sh->history_mark->begin = new;
	}
	sh->history_mark->size++;
}

void	init_history(t_42sh *sh, char *path)
{
	char *line;
	int fd;

	if (!(sh->history_mark = malloc(sizeof(t_history_mark))))
		print_error(_ENOMEM, 1);
	sh->history_mark->begin = NULL;
	sh->history_mark->last = NULL;
	sh->history_mark->cur = NULL;
	sh->history_mark->size = 0;
	sh->history_mark->pos = 0;
	sh->history_mark->error_code = 0;
	if (access(path, F_OK) == 0)
	{
		fd = open(path, O_RDWR);
		while (get_next_line(fd, &line) == 1)
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
	//parser(sh);
	add_to_list(sh, line);
	fd = open(path, O_CREAT | O_RDWR);
	lseek(fd, 0, SEEK_END);
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\0", fd);
	close(fd);
}
