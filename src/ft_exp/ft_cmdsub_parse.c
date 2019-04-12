/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsub_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:23:33 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:23:42 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_cmdsub_getast(t_ast *ast, t_42sh *shell)
{
	t_lex	lex;
	char	*line;

	while (ft_continue_line(shell, &line, NULL))
	{
		lex = (t_lex){line, 0, NULL, NULL, true, false, 0};
		if (ft_lexer(&lex, shell))
		{
			ft_ast_free(ast->begin);
			return (1);
		}
		ast->list = ft_toklist_to_node(lex.input, lex.begin);
		if (ft_build_ast(ast, shell))
			return (1);
	}
	return (0);
}

int			ft_cmdsub_parse(t_ast *ast, char *command, t_42sh *shell)
{
	char	*tmp_buffer;
	bool	tmp_buffer_mode;
	int		ret;

	tmp_buffer = shell->buffer;
	tmp_buffer_mode = shell->buffer_mode;
	shell->buffer = ft_strdup(command);
	shell->buffer_mode = true;
	ret = ft_cmdsub_getast(ast, shell);
	if (shell->buffer)
		free(shell->buffer);
	shell->buffer = tmp_buffer;
	shell->buffer_mode = tmp_buffer_mode;
	return (ret);
}
