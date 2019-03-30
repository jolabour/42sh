/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:52:23 by geargenc          #+#    #+#             */
/*   Updated: 2019/03/30 10:30:45 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_node			*ft_new_node(void)
{
	t_node		*new;

	if (!(new = (t_node *)ft_malloc_exit(sizeof(t_node))))
		return (NULL);
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
		if (!(*next = ft_new_node())
			|| !((*next)->data = ft_strsub(input, list->start, list->len)))
			return (NULL);
		(*next)->token = list->token;
		next = &((*next)->right);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	return (begin);
}

void			ft_ast_push_one_back_left(t_node **from, t_node *to)
{
	while (to->left)
		to = to->left;
	(*from)->parent = to;
	to->left = *from;
	*from = (*from)->right;
	to->left->right = NULL;
}

void			ft_ast_push_one_back_right(t_node **from, t_node *to)
{
	while (to->right)
		to = to->right;
	(*from)->parent = to;
	to->right = *from;
	*from = (*from)->right;
	to->right->right = NULL;
}

void			ft_ast_push_one_back_redir(t_node **from, t_node *to)
{
	while (to->redir)
		to = to->redir;
	(*from)->parent = to;
	to->redir = *from;
	*from = (*from)->right;
	to->redir->right = NULL;
}

int				ft_ast_badtoken(t_node **begin, t_node **current
				, t_node **list, t_42sh *shell)
{
	(void)begin;
	(void)current;
	(void)list;
	(void)shell;
	return (0);
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

int				ft_ast_isassignment(t_node *current, t_node *list)
{
	char		*equal;
	char		*word;

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

int				ft_ast_iscommand(t_node *current)
{
	return (current && (current->token == COMMAND || current->token == RPAR
		|| current->token == RBRACE));
}

int				ft_ast_isseparator(t_node *current)
{
	return (current && (current->token == SEMI || current->token == AND));
}

int				ft_ast_continue_list(t_node **list, t_42sh *shell)
{
	t_lex		lex;

	shell->prompt = "> ";
	prompt(shell->env, shell);
	ft_strdel(&(shell->stdin->input));
	free(shell->stdin);
	if (get_line(shell) != 1)
	{
		ft_putstr_fd("42sh: syntax error: unexpected end of file\n", 2);
		return (-1);
	}
	lex = (t_lex){shell->stdin->input, 0, NULL, NULL, true, false, 0};
	if (ft_lexer(&lex, shell))
		return (-1);
	*list = ft_toklist_to_node(lex.input, lex.begin);
	return (1);
}

int				ft_ast_isbreakline(t_node *current)
{
	return (current && (current->token == PIPE
		|| current->token == AND_IF
		|| current->token == OR_IF));
}

void			ft_ast_freeone(t_node **list)
{
	t_node		*tmp;

	tmp = *list;
	*list = (*list)->right;
	if (tmp->data)
		free(tmp->data);
	free(tmp);
}

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

int				ft_ast_readheredoc(t_node *heredoc, t_42sh *shell)
{
	char		*input;
	int			ret;

	(void)shell;
	input = NULL;
	while (!input)
	{
		ret = get_next_line(0, &input) == 1;
		if (ret == -1)
			return (-1);
		if (ret == 0)
		{
			ft_putstr_fd("42sh: Warning : here-document delimited by "
				"end-of-file\n", 2);
			return (1);
		}
		if (ft_strncmp(input, heredoc->right->data, ft_strlen(input) - 1))
		{
			if (!(heredoc->right->right->data =
				ft_strjoinfree(heredoc->right->right->data, input, 3)))
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
	t_node		*tmp;
	int			ret;

	tmp = *list;
	if ((ret = ft_ast_redir(begin, current, list, shell)) != 1)
		return (ret);
	if (!(tmp->right->right = ft_new_node())
		|| !(tmp->right->right->data = ft_strdup("")))
		return (-1);
	return (ft_ast_readheredoc(tmp, shell));
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

void			ft_ast_free(t_node *ast)
{
	if (ast)
	{
		if (ast->left)
			ft_ast_free(ast->left);
		if (ast->right)
			ft_ast_free(ast->right);
		if (ast->redir)
			ft_ast_free(ast->redir);
		if (ast->data)
			free(ast->data);
		free(ast);
	}
}

int				ft_ast_isincompound(t_node *current)
{
	while (current)
	{
		if (current->token == LPAR || current->token == LBRACE)
			return (1);
		current = current->parent;
	}
	return (0);
}

void			ft_line_spaces(int rec)
{
	while (rec > 0)
	{
		write(1, "    |", 5);
		rec--;
	}
}

#include <stdarg.h>

void			ft_printer(char *format, ...)
{
	va_list		ap;
	char		*res;
	int			i;

	va_start(ap, format);
	vasprintf(&res, format, ap);
	va_end(ap);
	i = 0;
	while (res[i])
	{
		if (res[i] == '\n')
			write(1, "\\n", 2);
		else
			write(1, res + i, 1);
		i++;
	}
	write(1, "\n", 1);
	free(res);
}

void			ft_print_ast(t_node *ast, int rec)
{
	ft_line_spaces(rec);
	ft_printer("    +token [%s]", g_tokstr[ast->token]);
	ft_line_spaces(rec);
	ft_printer("    +data [%s]", ast->data);
	if (ast->left)
	{
		ft_line_spaces(rec);
		ft_printer("    +left :");
		ft_print_ast(ast->left, rec + 1);
	}
	if (ast->right)
	{
		ft_line_spaces(rec);
		ft_printer("    +right :");
		ft_print_ast(ast->right, rec + 1);
	}
	if (ast->redir)
	{
		ft_line_spaces(rec);
		ft_printer("    +redirs :");
		ft_print_ast(ast->redir, rec + 1);
	}
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
			return (-1);
		}
	}
	// if (begin)
	// 	ft_print_ast(begin, 0);
	return (0);
}
