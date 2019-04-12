/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:27:45 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 08:32:54 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_node			*ft_new_node(void)
{
	t_node		*new;

	new = (t_node *)ft_malloc_exit(sizeof(t_node));
	ft_bzero(new, sizeof(t_node));
	return (new);
}

t_node			*ft_toklist_to_node(char *input, t_toklist *list)
{
	t_node		*begin;
	t_node		**next;
	t_toklist	*tmp;

	begin = NULL;
	next = &begin;
	while (list)
	{
		*next = ft_new_node();
		(*next)->data = ft_strsub(input, list->start, list->len);
		(*next)->token = list->token;
		next = &((*next)->right);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	free(input);
	return (begin);
}

void			ft_ast_insert_parent(t_node **begin, t_node **current,
				t_node **list)
{
	(*list)->parent = (*current)->parent;
	(*list)->left = *current;
	if (!((*list)->parent))
		*begin = *list;
	else if ((*current)->parent->right == *current)
		(*current)->parent->right = *list;
	else
		(*current)->parent->left = *list;
	(*current)->parent = *list;
	*current = *list;
	*list = (*list)->right;
	(*current)->right = NULL;
}

int				ft_ast_continue_list(t_node **list, t_42sh *shell)
{
	t_lex		lex;
	char		*line;
	int			ret;

	ret = ft_continue_line(shell, &line, NULL);
	if (ret != 1)
		return (ret);
	lex = (t_lex){line, 0, NULL, NULL, true, false, 0};
	if (ft_lexer(&lex, shell))
		return (-1);
	*list = ft_toklist_to_node(lex.input, lex.begin);
	return (1);
}
