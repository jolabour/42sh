/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:24:11 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 08:35:31 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_ast_isassignment(t_node *current, t_node *list)
{
	char	*equal;
	char	*word;

	if (!(current->right) && (equal = ft_strchr(list->data, '='))
		&& equal != list->data)
	{
		if (*(list->data) >= '0' && *(list->data) <= '9')
			return (0);
		word = list->data;
		while (word < equal)
		{
			if (*word != '_' && !ft_isalnum(*word))
				return (0);
			word++;
		}
		return (1);
	}
	return (0);
}

int			ft_ast_iscommand(t_node *current)
{
	return (current && (current->token == COMMAND || current->token == RPAR
		|| current->token == RBRACE));
}

int			ft_ast_isseparator(t_node *current)
{
	return (current && (current->token == SEMI || current->token == AND));
}

int			ft_ast_isbreakline(t_node *current)
{
	return (current && (current->token == PIPE
		|| current->token == AND_IF
		|| current->token == OR_IF));
}

int			ft_ast_isincompound(t_node *current)
{
	while (current)
	{
		if (current->token == LPAR || current->token == LBRACE)
			return (1);
		current = current->parent;
	}
	return (0);
}
