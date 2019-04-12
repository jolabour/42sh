/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_push_one_back.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:33:06 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 08:34:55 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_ast_push_one_back_left(t_node **from, t_node *to)
{
	while (to->left)
		to = to->left;
	(*from)->parent = to;
	to->left = *from;
	*from = (*from)->right;
	to->left->right = NULL;
}

void		ft_ast_push_one_back_right(t_node **from, t_node *to)
{
	while (to->right)
		to = to->right;
	(*from)->parent = to;
	to->right = *from;
	*from = (*from)->right;
	to->right->right = NULL;
}

void		ft_ast_push_one_back_redir(t_node **from, t_node *to)
{
	while (to->redir)
		to = to->redir;
	(*from)->parent = to;
	to->redir = *from;
	*from = (*from)->right;
	to->redir->right = NULL;
}
