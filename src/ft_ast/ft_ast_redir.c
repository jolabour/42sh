/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 08:10:19 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/20 04:03:19 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_ast_io_number(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	t_node		*io_number;

	(void)begin;
	(void)current;
	(void)shell;
	io_number = *list;
	*list = (*list)->right;
	io_number->right = NULL;
	(*list)->left = io_number;
	return (1);
}

int				ft_ast_redir(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	t_node		*tmp;

	(void)shell;
	if (!ft_ast_iscommand(*current)
		&& ft_ast_command(begin, current) == -1)
		return (-1);
	tmp = *list;
	ft_ast_push_one_back_redir(list, *current);
	if (!(*list) || (*list)->token != WORD)
		return (0);
	ft_ast_push_one_back_right(list, tmp);
	return (1);
}

int				ft_ast_readheredoc(t_node *heredoc, char *delim, t_42sh *shell)
{
	char		*input;
	int			ret;

	input = NULL;
	while (!input)
	{
		ret = ft_continue_line(shell, &input, NULL);
		if (ret == -1)
			return (-1);
		if (ret == 0)
		{
			ft_putstr_fd("42sh: Warning : here-document delimited by "
				"end-of-file\n", STDERR_FILENO);
			return (1);
		}
		if (!ft_strnequ(input, delim, ft_strlen(delim)))
		{
			if (!(heredoc->data = ft_strjoinfree(heredoc->data, input, 3)))
				return (-1);
			input = NULL;
		}
	}
	free(input);
	return (1);
}

int				ft_ast_heredoc(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	char		*delim;
	t_node		*tmp;
	int			ret;

	tmp = *list;
	if ((ret = ft_ast_redir(begin, current, list, shell)) != 1)
		return (ret);
	delim = ft_strdup(tmp->right->data);
	ft_rmquotes_word(delim);
	tmp->right->right = ft_new_node();
	tmp = tmp->right->right;
	tmp->data = ft_strdup("");
	ret = ft_ast_readheredoc(tmp, delim, shell);
	free(delim);
	return (ret);
}

int				ft_ast_closefd(t_node **begin, t_node **current,
				t_node **list, t_42sh *shell)
{
	(void)shell;
	if (!ft_ast_iscommand(*current)
		&& ft_ast_command(begin, current) == -1)
		return (-1);
	ft_ast_push_one_back_redir(list, *current);
	return (1);
}
