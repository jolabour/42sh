/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:15:18 by ttresori          #+#    #+#             */
/*   Updated: 2019/04/05 02:35:49 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_substitute_histo(t_42sh *sh, int *i, int *nb_del)
{
	char *substitute;

	substitute = NULL;
	if (sh->stdin->input[*i + 1] == '!')
	{
		substitute = ft_strdup(sh->history_mark->begin->next->str);
		*nb_del = 2;
	}
	else if (sh->stdin->input[*i + 1] == '-')
		substitute = search_history_last(sh, get_nb_history(sh, *i, nb_del));
	else if (sh->stdin->input[*i + 1] >= '0' && sh->stdin->input[*i + 1] <= '9')
	{
		substitute = search_history_begin(sh, get_nb_history(sh, *i, nb_del));
	}
	else if (ft_isprint(sh->stdin->input[*i + 1]) == 1 &&
		sh->stdin->input[*i + 1] != '=' &&
		sh->stdin->input[*i + 1] != '}' && sh->stdin->input[*i + 1] != ' ')
		substitute = search_str_input(sh, *i + 1, nb_del);
	else
		substitute = ft_strdup("\0");
	return (substitute);
}

int		substitute_history(t_42sh *sh, int *i)
{
	char	*substitute;
	int		nb_del;

	nb_del = 0;
	substitute = get_substitute_histo(sh, i, &nb_del);
	if (substitute == NULL)
	{
		ft_putendl_fd("42sh: event not found", 2);
		return (sh->retval = 1);
	}
	if (substitute[0] == '\0')
	{
		*i = *i + 1;
		return (0);
	}
	get_substitute(sh, *i, substitute, nb_del);
	*i += ft_strlen(substitute) - 1;
	free(substitute);
	return (0);
}

int		check_substitute_history(t_42sh *sh)
{
	int i;

	if (sh->history_mark->size == 1)
		return (1);
	i = 0;
	while (sh->stdin->input[i])
	{
		if (sh->stdin->input[i] == '!')
			if (substitute_history(sh, &i) == 1)
				return (0);
		i++;
	}
	return (1);
}
