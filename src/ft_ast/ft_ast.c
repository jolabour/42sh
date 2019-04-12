/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:52:23 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 08:39:32 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_error_unexpected(t_node *list)
{
	ft_putstr_fd("42sh", 2);
	if (list)
	{
		ft_putstr_fd(": syntax error near unexpected token `", 2);
		if (list->token == NEWLINE)
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(list->data, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
		ft_putstr_fd(": syntax error: unexpected end of file\n", 2);
}

int				ft_build_ast(t_ast *ast, t_42sh *shell)
{
	int			ret;

	while (ast->list)
	{
		ret = g_asttab[ast->list->token](&(ast->begin), &(ast->current),
			&(ast->list), shell);
		if (ret == 1 && !ast->list && (ft_ast_isbreakline(ast->current)
			|| ft_ast_isincompound(ast->current)))
			ret = ft_ast_continue_list(&(ast->list), shell);
		if (ret != 1)
		{
			if (ret == 0)
				ft_error_unexpected(ast->list);
			ft_ast_free(ast->begin);
			ft_ast_free(ast->list);
			*ast = (t_ast){NULL, NULL, NULL};
			return (-1);
		}
	}
	return (0);
}
