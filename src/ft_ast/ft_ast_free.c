/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:29:42 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 08:30:44 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_ast_freeone(t_node **list)
{
	t_node		*tmp;

	tmp = *list;
	*list = (*list)->right;
	if (tmp->data)
		free(tmp->data);
	free(tmp);
}

void			ft_ast_free(t_node *ast)
{
	if (ast)
	{
		ft_ast_free(ast->left);
		ft_ast_free(ast->right);
		ft_ast_free(ast->redir);
		if (ast->data)
			free(ast->data);
		free(ast);
	}
}
