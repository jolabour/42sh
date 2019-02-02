/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:21:10 by ttresori          #+#    #+#             */
/*   Updated: 2019/01/25 02:58:32 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "dirent.h"

int		show_name(char *str_to_find, char *path)
{
	DIR	*directory;
	struct dirent *name;
	int i;

	i = 0;
	directory = opendir(path);
	name = readdir(directory);
	while (name->d_name[i])
		ft_putendl(&name->d_name[i++]);
	(void)str_to_find;
	return (0);
}

void	show_suggest(t_42sh *sh)
{
//	DIR		*directory;
//	char	*path;
	char	*str_to_find;
	char	**line;
	int		save_pos;
	int		i;
	
	save_pos = sh->argv->pos_str;
	str_to_find = ft_strnew(ft_strlen(sh->stdin->input) + 1);
	i = 0;
	str_to_find[save_pos + 1] = '\0';
	while (save_pos >= 0)
	{
		str_to_find[save_pos] = sh->stdin->input[save_pos];
		save_pos--;
	}
	if (!((line = ft_strsplitset(sh->stdin->input, " \t\n"))))
		show_name(str_to_find, "./");
	else
	{
		show_name(str_to_find, line[1]);
		ft_free_split(line);
	}
	free(str_to_find);
//	directory = NULL;
}
