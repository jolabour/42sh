/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 07:36:12 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 08:09:38 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_ast_lpar(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	(void)shell;
	if (*current && (*current)->token == COMMAND)
		return (0);
	if (*current)
	{
		ft_ast_push_one_back_right(list, *current);
		*current = (*current)->right;
	}
	else
	{
		*begin = *list;
		*current = *list;
		*list = (*list)->right;
		(*current)->right = NULL;
	}
	return (1);
}

int				ft_ast_rpar(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	t_node		*tmp;

	(void)begin;
	(void)shell;
	if (!ft_ast_iscommand(*current) && !ft_ast_isseparator(*current))
		return (0);
	while (*current && (*current)->token != LPAR && (*current)->token != LBRACE)
		*current = (*current)->parent;
	if (*current && (*current)->token == LPAR)
		(*current)->token = RPAR;
	else
		return (0);
	tmp = *list;
	*list = (*list)->right;
	free(tmp->data);
	free(tmp);
	return (1);
}

int				ft_ast_lbrace(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	(void)shell;
	if (*current && (*current)->token == COMMAND)
		return (0);
	if (*current)
	{
		ft_ast_push_one_back_right(list, *current);
		*current = (*current)->right;
	}
	else
	{
		*begin = *list;
		*current = *list;
		*list = (*list)->right;
		(*current)->right = NULL;
	}
	return (1);
}

int				ft_ast_rbrace(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	t_node		*tmp;

	(void)begin;
	(void)shell;
	if (!ft_ast_iscommand(*current) && !ft_ast_isseparator(*current))
		return (0);
	while (*current && (*current)->token != LPAR && (*current)->token != LBRACE)
		*current = (*current)->parent;
	if (*current && (*current)->token == LBRACE)
		(*current)->token = RBRACE;
	else
		return (0);
	tmp = *list;
	*list = (*list)->right;
	free(tmp->data);
	free(tmp);
	return (1);
}
