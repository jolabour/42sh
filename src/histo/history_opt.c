/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:26:21 by ttresori          #+#    #+#             */
/*   Updated: 2018/12/13 05:24:02 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void clean_history(char *path)
{
	unlink(path);
//	add_history("\t0  [START]", path);
}

/*void	print_history(char *path, int start)
{
	char *get_line;
	int fd;
	int i;

	if (!(fd = open(path, O_RDWR)))
		ft_putendl_fd("Can't open [.42sh_history] file", 2);
	i = 0;
	while (get_next_line(fd, &get_line) == 1)
    {
		if (i++ >= start)
			ft_putendl_fd(get_line, 0);
        free(get_line);
    }
	close (fd);
}
*/
void	print_history_n(char *path)
{
	char *get_line;
	int fd;
	int i;
		
	fd = open(path, O_RDWR);
	i = 0;
	while (get_next_line(fd, &get_line) == 1)
    {
		while (get_line[i])
		{
			if (i > 4)
				ft_putchar(get_line[i]);
			i++;
		}
		ft_putchar('\n');
		i = 0;
        free(get_line);
    }
	close (fd);
}

void	print_history_r(char *path)
{
	char 	*get_line;
	char	**str;
	int fd;
	int i;
		
	if (!(fd = open(path, O_RDWR)))
		ft_putendl_fd("Can't open [.42sh_history] file", 2);
	i = 0;
	while (get_next_line(fd, &get_line) == 1)
    {
		i++;
        free(get_line);
    }
	close (fd);
	if (!(str = (char**)malloc(sizeof(char*) * (i))))
		return ;
	if (!(fd = open(path, O_RDWR)))
		ft_putendl_fd("Can't open [.42sh_history] file", 2);
	i = 0;
	while (get_next_line(fd, &get_line) == 1)
    {
		str[i++] = ft_strdup(get_line);
        free(get_line);
    }
	i = i - 1;
	while (i > 0)
	{
		ft_putendl(str[i]);
		free(str[i--]);
	}
	free(str[i]);
	free(str);
	close (fd);
	
}

void	history_p(t_42sh *sh)
{
	sh->lexer = sh->lexer->next;
	sh->lexer = sh->lexer->next;
	while (sh->lexer->str != NULL)
	{
		ft_putendl(sh->lexer->str);
		sh->lexer = sh->lexer->next;
	}
}
