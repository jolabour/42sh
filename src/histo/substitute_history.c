/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 04:18:59 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/03 04:27:03 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		modify_last_history(t_42sh *sh)
{
	int		i;
	int		i2;
	int		size;
	int		nb_replace;
	int		fd;

	i = 0;
	i2 = 0;
	size = 0;
	fd = 0;
	nb_replace = 0;
	add_to_list(sh, sh->history_mark->last_str);
	fd = open(sh->path_history, O_RDWR);
	lseek(fd, sh->history_mark->size + 1, SEEK_END);
	ft_putstr_fd(sh->history_mark->last_str, fd);
	ft_putendl_fd("\0", fd);
	free(sh->history_mark->last_str);
	sh->history_mark->last_str = NULL;
	close(fd);
}

char		*search_str_input(t_42sh *sh, int start, int *nb_del)
{
	int		i;
	char	*str_to_find;
	char	*sub;

	str_to_find = NULL;
	sub = NULL;
	i = 0;
	str_to_find = (char*)ft_malloc_exit(sizeof(char) *
		(sh->stdin->len_line + 1));
	while (sh->stdin->input[start]
			&& (sh->stdin->input[start] != ' '
				&& sh->stdin->input[start] != '\t')
			&& sh->stdin->input[start] != '!'
			&& sh->stdin->input[start] != '\n')
	{
		str_to_find[i] = sh->stdin->input[start];
		i++;
		start++;
	}
	str_to_find[i] = '\0';
	*nb_del = ft_strlen(str_to_find) + 1;
	sub = search_history_char(sh, &str_to_find);
	ft_strdel(&str_to_find);
	return (sub);
}

void		get_substitute(t_42sh *sh, int i, char *substitute, int nb_del)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	if (i != 0)
	{
		tmp = ft_strsub(sh->stdin->input, 0, i);
		tmp3 = ft_strjoin(tmp, substitute);
	}
	else
	{
		tmp3 = ft_strdup(substitute);
		tmp = ft_strdup("");
	}
	tmp2 = ft_strsub(sh->stdin->input, i + nb_del, ft_strlen(sh->stdin->input)
			- ft_strlen(tmp) - nb_del);
	ft_strdel(&sh->stdin->input);
	sh->stdin->input = ft_strjoin(tmp3, tmp2);
	ft_putstr(sh->stdin->input);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	ft_strdel(&tmp3);
}

int			get_nb_history(t_42sh *sh, int pos, int *nb_del)
{
	int		i;
	int		nb;
	char	*nb_to_find;

	i = 0;
	nb_to_find = ft_malloc_exit(sizeof(char) * ft_strlen(sh->stdin->input));
	if (sh->stdin->input[pos + 1] == '-' && (sh->stdin->input[pos + 2] >= '0'
				&& sh->stdin->input[pos + 2] <= '9'))
	{
		nb_to_find[i] = '-';
		i++;
		pos++;
	}
	while (sh->stdin->input[pos + 1] && (sh->stdin->input[pos + 1] >= '0'
				&& sh->stdin->input[pos + 1] <= '9'))
	{
		nb_to_find[i] = sh->stdin->input[pos + 1];
		i++;
		pos++;
	}
	nb_to_find[i] = '\0';
	*nb_del = ft_strlen(nb_to_find) + 1;
	nb = ft_atoi(nb_to_find);
	ft_strdel(&nb_to_find);
	return (nb);
}
