/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:26:21 by ttresori          #+#    #+#             */
/*   Updated: 2019/03/27 00:43:38 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void clean_history(char *path)
{
	int fd;
	
	unlink(path);
	fd = open(path, O_CREAT | O_RDWR);
	close(fd);
}

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
	str = (char**)ft_malloc_exit(sizeof(char*) * (i));
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
