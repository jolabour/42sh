/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:49:50 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/20 04:04:27 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_free_last_toklist(t_lex *lex)
{
	t_toklist	**tmp;

	tmp = &(lex->begin);
	while ((*tmp)->next)
		tmp = &((*tmp)->next);
	if (*tmp)
		free(*tmp);
	*tmp = NULL;
	lex->current = lex->begin;
	if (lex->current)
		while (lex->current->next)
			lex->current = lex->current->next;
}

void			ft_lex_replace_alias(t_lex *lex, char *alias)
{
	char		*new;

	new = (char *)ft_malloc_exit((ft_strlen(lex->input) + ft_strlen(alias)
		- lex->current->len + 1) * sizeof(char));
	ft_strncpy(new, lex->input, lex->current->start);
	ft_strcpy(new + lex->current->start, alias);
	ft_strcpy(new + lex->current->start + ft_strlen(alias),
		lex->input + lex->current->start + lex->current->len);
	free(lex->input);
	lex->input = new;
	lex->index = lex->current->start;
	ft_free_last_toklist(lex);
}

void			ft_lex_assignment(t_lex *lex)
{
	size_t		i;

	i = lex->current->start;
	if (ft_isalpha(lex->input[i]) || lex->input[i] == '_')
	{
		while (ft_isalnum(lex->input[i]) || lex->input[i] == '_')
			i++;
	}
	if (i == lex->current->start || lex->input[i] != '=')
		lex->alias_recognition = false;
}

char			*ft_check_alias_condition(t_lex *lex, t_42sh *shell)
{
	char		*name;
	char		*alias;
	size_t		alias_len;

	name = ft_strsub(lex->input, lex->current->start, lex->current->len);
	if (ft_check_alias_lock(&(lex->lock), lex->index, name)
		|| !(alias = substitute_alias(name, shell)))
	{
		free(name);
		return (NULL);
	}
	alias_len = ft_strlen(alias);
	ft_add_len_alias_lock(lex->lock, alias_len - lex->current->len);
	ft_add_alias_lock(&(lex->lock), name, lex->current->start + alias_len);
	return (alias);
}

int				ft_lex_delimiter(t_lex *lex, t_42sh *shell)
{
	char		*alias;

	if (!lex->current || lex->current->token != WORD || lex->index
			!= lex->current->start + lex->current->len)
		return (0);
	if (lex->redir_op)
	{
		lex->redir_op = false;
		return (0);
	}
	if (!lex->alias_recognition)
		return (0);
	if ((alias = ft_check_alias_condition(lex, shell)))
	{
		ft_lex_replace_alias(lex, alias);
		free(alias);
		return (1);
	}
	ft_lex_assignment(lex);
	return (0);
}
