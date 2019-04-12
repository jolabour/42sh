/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:37:54 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 08:38:12 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_ast_command(t_node **begin, t_node **current)
{
	t_node		*command;

	if (!(*current) || (*current)->token != COMMAND)
	{
		if (!(command = ft_new_node()))
			return (-1);
		command->token = COMMAND;
		if (!(*begin))
		{
			*begin = command;
			*current = command;
		}
		else
		{
			(*current)->right = command;
			command->parent = *current;
			*current = command;
		}
	}
	return (1);
}

int				ft_ast_word(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	(void)shell;
	if (*current && ((*current)->token == RPAR || (*current)->token == RBRACE))
		return (0);
	if (ft_ast_command(begin, current) == -1)
		return (-1);
	if (ft_ast_isassignment(*current, *list))
		ft_ast_push_one_back_left(list, *current);
	else
		ft_ast_push_one_back_right(list, *current);
	return (1);
}
