/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_separators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:14:56 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 08:15:36 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_ast_newline(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	(void)shell;
	if (ft_ast_iscommand(*current))
	{
		(*list)->token = SEMI;
		(*list)->data[0] = ';';
		return (ft_ast_separator(begin, current, list, shell));
	}
	ft_ast_freeone(list);
	return (1);
}

int				ft_ast_pipe(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	(void)shell;
	if (!ft_ast_iscommand(*current))
		return (0);
	ft_ast_insert_parent(begin, current, list);
	return (1);
}

int				ft_ast_separator(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	(void)shell;
	if (!ft_ast_iscommand(*current))
		return (0);
	while ((*current)->parent && ((*current)->parent->token == PIPE
		|| (*current)->parent->token == AND_IF
		|| (*current)->parent->token == OR_IF))
		*current = (*current)->parent;
	ft_ast_insert_parent(begin, current, list);
	return (1);
}

int				ft_ast_and_or(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	(void)shell;
	if (!ft_ast_iscommand(*current))
		return (0);
	while ((*current)->parent && ((*current)->parent->token == PIPE
		|| (*current)->parent->token == AND_IF
		|| (*current)->parent->token == OR_IF))
		*current = (*current)->parent;
	ft_ast_insert_parent(begin, current, list);
	return (1);
}
