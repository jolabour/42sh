/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 07:06:58 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 20:59:08 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_toklist		*ft_newtoklist(void)
{
	t_toklist	*new;

	new = (t_toklist *)ft_malloc_exit(sizeof(t_toklist));
	ft_bzero(new, sizeof(t_toklist));
	return (new);
}

void			ft_add_toklist(t_lex *lex, t_tok token)
{
	if (!lex->begin)
	{
		lex->begin = ft_newtoklist();
		lex->current = lex->begin;
	}
	else
	{
		if (lex->current->token != NONE)
			lex->current->next = ft_newtoklist();
		lex->current = lex->current->next;
	}
	lex->current->token = token;
}

int				ft_lex_continue_line(t_lex *lex, t_42sh *shell, char *matching)
{
	char		*line;
	int			ret;

	ret = ft_continue_line(shell, &line, matching);
	if (line)
		lex->input = ft_strjoinfree(lex->input, line, 3);
	return (ret);
}

void			ft_lex_free(t_lex *lex)
{
	t_toklist	*tmp;

	while (lex->begin)
	{
		tmp = lex->begin;
		lex->begin = lex->begin->next;
		free(tmp);
	}
	free(lex->input);
	ft_free_alias_lock(&(lex->lock));
}
