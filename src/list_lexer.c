/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:25:50 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/13 04:29:15 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_lexer		*create_token(char *str, int token_type, int operator_type)
{
	t_lexer	*new;

	if (!(new = malloc(sizeof(t_lexer))))
		return (NULL);
	new->str = ft_strdup(str);
	new->token_type = token_type;
	new->operator_type = operator_type;
	new->next = NULL;
	return (new);
}

void		lst_push_lexer(t_lexer **head, t_lexer *new)
{
	t_lexer	*tmp;

	if (*head ==NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		add_token(t_42sh *sh, char *str, int token_type, int operator_type)
{
	t_lexer *tmp;
	t_lexer *new;

	tmp = sh->lexer;
	if (!(new = create_token(str, token_type, operator_type)))
		print_error(_ENOMEM, 1);
	if (sh->token_nbr == 0)
	{
		sh->lexer = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void		del_last(t_lexer **lexer)
{
	t_lexer		*tmp;
	t_lexer		*prev;

	tmp = *lexer;
	prev = tmp;
	while (tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = NULL;
	ft_strdel(&tmp->str);
	free(tmp);
	tmp = NULL;
}

void		del_lexer(t_lexer **lexer)
{
	t_lexer *tmp;
	t_lexer *prev;

	tmp = *lexer;
	while (tmp)
	{
		free(tmp->str);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
}
