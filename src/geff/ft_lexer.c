/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 01:47:25 by geargenc          #+#    #+#             */
/*   Updated: 2019/03/30 10:39:48 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_toklist		*ft_newtoklist(void)
{
	t_toklist	*new;

	new = (t_toklist *)ft_malloc_exit(sizeof(t_toklist));
	ft_bzero(new, sizeof(t_toklist));
	return (new);
}

void			ft_add_toklist(t_lex *lex, t_tok token)
{
	if (!lex->begin)
	{
		lex->begin = ft_newtoklist();
		lex->current = lex->begin;
	}
	else
	{
		if (lex->current->token != NONE)
			lex->current->next = ft_newtoklist();
		lex->current = lex->current->next;
	}
	lex->current->token = token;
}

char		*ft_strjoinfree(char *s1, char *s2, unsigned int which)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	join = (char *)ft_malloc_exit(i + j + 1);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	if (which == 1 || which > 2)
		free(s1);
	if (which > 1)
		free(s2);
	return (join);
}

int				ft_continue_line(t_lex *lex, t_42sh *shell)
{
	shell->prompt = "> ";
	prompt(shell->env, shell);
	free(shell->stdin);
	if (get_line(shell) != 1)
	{
		ft_putstr_fd("42sh: syntax error: unexpected end of file\n", 2);
		return (-1);
	}
	shell->stdin->input = ft_strjoinfree(lex->input, shell->stdin->input, 3);
	lex->input = shell->stdin->input;
	return (0);
}

void			ft_free_last_toklist(t_lex *lex)
{
	t_toklist	**tmp;

	tmp = &(lex->begin);
	while ((*tmp)->next)
		tmp = &((*tmp)->next);
	if (*tmp)
		free(*tmp);
	*tmp = NULL;
	lex->current = lex->begin;
	if (lex->current)
		while (lex->current->next)
			lex->current = lex->current->next;
}

void			ft_lex_replace_alias(t_lex *lex, char *alias, t_42sh *shell)
{
	char		*new;

	lex->ignore_alias = lex->current->start + ft_strlen(alias);
	new = (char *)ft_malloc_exit((ft_strlen(lex->input) + ft_strlen(alias)
		- lex->current->len + 1) * sizeof(char));
	ft_strncpy(new, lex->input, lex->current->start);
	ft_strcpy(new + lex->current->start, alias);
	ft_strcpy(new + lex->current->start + ft_strlen(alias),
		lex->input + lex->current->start + lex->current->len);
	free(lex->input);
	lex->input = new;
	shell->stdin->input = new;
	lex->index = lex->current->start;
	ft_free_last_toklist(lex);
}

void			ft_lex_assignment(t_lex *lex)
{
	size_t		i;

	i = lex->current->start;
	if (ft_isalpha(lex->input[i]) || lex->input[i] == '_')
	{
		while (ft_isalnum(lex->input[i]) || lex->input[i] == '_')
			i++;
	}
	if (i == lex->current->start || lex->input[i] != '=')
		lex->alias_recognition = false;
}

int				ft_lex_delimiter(t_lex *lex, t_42sh *shell)
{
	char		*alias;

	if (!lex->current || lex->current->token != WORD || lex->index !=
		lex->current->start + lex->current->len)
		return (0);
	if (lex->redir_op)
	{
		lex->redir_op = false;
		return (0);
	}
	if (!lex->alias_recognition || lex->current->start < lex->ignore_alias)
		return (0);
	alias = substitute_alias(ft_strsub(lex->input, lex->current->start,
		lex->current->len), shell);
	if (alias)
	{
		ft_lex_replace_alias(lex, alias, shell);
		free(alias);
		return (1);
	}
	ft_lex_assignment(lex);
	return (0);
}

int				ft_lex_newline(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '\n')
	{
		if (ft_lex_delimiter(lex, shell))
			return (0);
		ft_add_toklist(lex, NEWLINE);
		lex->alias_recognition = true;
		lex->current->start = lex->index;
		lex->current->len = 1;
		lex->index++;
		return (0);
	}
	return (1);
}

// int				ft_lex_newline(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	(void)shell;
// 	if ((*input)[*index] == '\n')
// 	{
// 		if ((*current)->token != NONE)
// 		{
// 			if (!((*current)->next = ft_newtoklist()))
// 				return (-1);
// 			*current = (*current)->next;
// 		}
// 		(*current)->token = NEWLINE;
// 		(*current)->start = *index;
// 		(*current)->len = 1;
// 		return (0);
// 	}
// 	return (1);
// }

// int				ft_lex_operator(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	size_t		i;
// 	size_t		j;

// 	(void)shell;
// 	if ((*current)->token == OPP)
// 	{
// 		i = 0;
// 		while (g_toktab[i].str)
// 		{
// 			j = 0;
// 			while (j < (*current)->len && g_toktab[i].str[j] ==
// 				(*input)[(*current)->start + j])
// 				j++;
// 			if (j == (*current)->len && g_toktab[i].str[j] ==
// 				(*input)[*index])
// 			{
// 				(*current)->len++;
// 				return (0);
// 			}
// 			i++;
// 		}
// 	}
// 	return (1);
// }

// int				ft_lex_notoperator(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	size_t		i;
// 	size_t		j;

// 	(void)index;
// 	(void)shell;
// 	if ((*current)->token == OPP)
// 	{
// 		i = 0;
// 		while (g_toktab[i].str)
// 		{
// 			j = 0;
// 			while (j < (*current)->len && g_toktab[i].str[j] ==
// 				(*input)[(*current)->start + j])
// 				j++;
// 			if (j == (*current)->len && g_toktab[i].str[j] == '\0')
// 			{
// 				(*current)->token = g_toktab[i].token;
// 				if (!((*current)->next = ft_newtoklist()))
// 					return (-1);
// 				*current = (*current)->next;
// 				return (1);
// 			}
// 			i++;
// 		}
// 	}
// 	return (1);
// }

int				ft_lex_backslash(t_lex *lex, t_42sh *shell)
{
	(void)shell;
	if (lex->input[lex->index] == '\\')
	{
		if (lex->input[lex->index + 1] == '\0'
			|| lex->input[lex->index + 1] == '\n')
		{
			lex->input[lex->index] = '\0';
			if (ft_continue_line(lex, shell) == -1)
				return (-1);
		}
		else
		{
			ft_lex_word(lex, shell);
			ft_lex_word(lex, shell);
		}
		return (0);
	}
	return (1);
}

// int				ft_lex_backslash(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	(void)shell;
// 	if ((*input)[*index] == '\\')
// 	{
// 		if ((*current)->token != WORD)
// 		{
// 			if (ft_lex_newword(input, index, current, shell) == -1)
// 				return (-1);
// 		}
// 		else
// 			(*current)->len++;
// 		(*current)->len++;
// 		(*index)++;
// 		return (0);
// 	}
// 	return (1);
// }

int				ft_lex_quote(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '\'')
	{
		ft_lex_word(lex, shell);
		while (lex->input[lex->index] != '\'')
		{
			if (lex->input[lex->index] == '\0')
			{
				if (ft_continue_line(lex, shell))
				{
					ft_putstr_fd(EOFWHILELOOK"`\''\n", 2);
					return (-1);
				}
			}
			else
				ft_lex_word(lex, shell);
		}
		ft_lex_word(lex, shell);
		return (0);
	}
	return (1);
}

// int				ft_lex_quote(char **input, size_t *index, t_toklist **current, t_42sh *shell)
// {
// 	if ((*input)[*index] == '\'')
// 	{
// 		if ((*current)->token != WORD)
// 		{
// 			if (ft_lex_newword(input, index, current, shell) == -1)
// 				return (-1);
// 		}
// 		else
// 			(*current)->len++;
// 		(*index)++;
// 		(*current)->len++;
// 		while ((*input)[*index] != '\'')
// 		{
// 			if ((*input)[*index] == '\0')
// 			{
// 				if (!(*input = ft_continue_line(*input, shell)))
// 					return (-1);
// 			}
// 			else
// 			{
// 				(*current)->len++;
// 				(*index)++;
// 			}
// 		}
// 		return (0);
// 	}
// 	return (1);
// }

// int				ft_lex_dquote_mode(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	int			i;
// 	int			ret;

// 	while ((*input)[*index] != '\"')
// 	{
// 		if ((*input)[*index] == '\0')
// 		{
// 			if (!(*input = ft_continue_line(*input, shell)))
// 				return (-1);
// 		}
// 		else
// 		{
// 			i = 0;
// 			while (g_tokcond[i].dquote_mode == 0 ||
// 				(ret = g_tokcond[i].cond(input, index, current, shell)) > 0)
// 				i++;
// 			if (ret == -1)
// 				return (-1);
// 			(*index)++;
// 		}
// 	}
// 	(*current)->len++;
// 	return (0);
// }

int				ft_lex_dquote_mode(t_lex *lex, t_42sh *shell)
{
	int			i;
	int			ret;

	while (lex->input[lex->index] != '\"')
	{
		if (lex->input[lex->index] == '\0')
		{
			if (ft_continue_line(lex, shell))
			{
				ft_putstr_fd(EOFWHILELOOK"`\"'\n", 2);
				return (-1);
			}
		}
		else
		{
			i = 0;
			while (g_tokcond[i].dquote_mode == 0 ||
				(ret = g_tokcond[i].cond(lex, shell)) > 0)
				i++;
			if (ret == -1)
				return (-1);
		}
	}
	return (0);
}

int				ft_lex_dquote(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '\"')
	{
		ft_lex_word(lex, shell);
		if (ft_lex_dquote_mode(lex, shell))
			return (-1);
		ft_lex_word(lex, shell);
		return (0);
	}
	return (1);
}

// int				ft_lex_dquote(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	if ((*input)[*index] == '\"')
// 	{
// 		if ((*current)->token != WORD)
// 		{
// 			if (ft_lex_newword(input, index, current, shell) == -1)
// 				return (-1);
// 		}
// 		else
// 			(*current)->len++;
// 		(*index)++;
// 		return (ft_lex_dquote_mode(input, index, current, shell));
// 	}
// 	return (1);
// }

// int				ft_lex_dollar_brace(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	size_t		i;
// 	int			braces;
// 	int			ret;

// 	braces = 1;
// 	while (braces)
// 	{
// 		(*index)++;
// 		if ((*input)[*index] == '\0'
// 			&& !(*input = ft_continue_line(*input, shell)))
// 			return (-1);
// 		if ((*input)[*index] == '{')
// 			braces++;
// 		else if ((*input)[*index] == '}')
// 			braces--;
// 		i = 0;
// 		while (g_tokcond[i].sub_mode == 0 ||
// 			(ret = g_tokcond[i].cond(input, index, current, shell)) > 0)
// 			i++;
// 		if (ret == -1)
// 			return (-1);
// 	}
// 	return (0);
// }

// int				ft_lex_dollar_par(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	size_t		i;
// 	int			pars;
// 	int			ret;

// 	pars = 1;
// 	while (pars)
// 	{
// 		(*index)++;
// 		if ((*input)[*index] == '\0'
// 			&& !(*input = ft_continue_line(*input, shell)))
// 			return (-1);
// 		if ((*input)[*index] == '(')
// 			pars++;
// 		else if ((*input)[*index] == ')')
// 			pars--;
// 		i = 0;
// 		while (g_tokcond[i].sub_mode == 0 ||
// 			(ret = g_tokcond[i].cond(input, index, current, shell)) > 0)
// 			i++;
// 		if (ret == -1)
// 			return (-1);
// 	}
// 	return (0);
// }

// int				ft_lex_dollar_mode(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	if ((*input)[*index] == '{')
// 	{
// 		(*current)->len++;
// 		return (ft_lex_dollar_brace(input, index, current, shell));
// 	}
// 	else if ((*input)[*index] == '(')
// 	{
// 		(*current)->len++;
// 		return (ft_lex_dollar_par(input, index, current, shell));
// 	}
// 	(*index)--;
// 	return (0);
// }

int				ft_lex_sub_mode(t_lex *lex, t_42sh *shell)
{
	int			i;
	int			ret;

	i = 0;
	while (g_tokcond[i].sub_mode == 0
		|| (ret = g_tokcond[i].cond(lex, shell)) > 0)
		i++;
	return (ret);
}

int				ft_lex_dollar_brace(t_lex *lex, t_42sh *shell)
{
	int			braces;

	braces = 1;
	ft_lex_word(lex, shell);
	while (braces)
	{
		if (lex->input[lex->index] == '\0')
		{
			if (ft_continue_line(lex, shell))
			{
				ft_putstr_fd(EOFWHILELOOK"`}'\n", 2);
				return (-1);
			}
		}
		else
		{
			if (lex->input[lex->index] == '{')
				braces++;
			if (lex->input[lex->index] == '}')
				braces--;
			if (ft_lex_sub_mode(lex, shell))
				return (-1);
		}
	}
	return (0);
}

int				ft_lex_dollar_par(t_lex *lex, t_42sh *shell)
{
	int			pars;

	pars = 1;
	ft_lex_word(lex, shell);
	while (pars)
	{
		if (lex->input[lex->index] == '\0')
		{
			if (ft_continue_line(lex, shell))
			{
				ft_putstr_fd(EOFWHILELOOK"`)'\n", 2);
				return (-1);
			}
		}
		else
		{
			if (lex->input[lex->index] == '(')
				pars++;
			if (lex->input[lex->index] == ')')
				pars--;
			if (ft_lex_sub_mode(lex, shell))
				return (-1);
		}
	}
	return (0);
}

int				ft_lex_dollar(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '$')
	{
		ft_lex_word(lex, shell);
		if (lex->input[lex->index] == '{')
			return (ft_lex_dollar_brace(lex, shell));
		if (lex->input[lex->index] == '(')
			return (ft_lex_dollar_par(lex, shell));
		if (ft_get_spparam(lex->input[lex->index]))
			ft_lex_word(lex, shell);
		return (0);
	}
	return (1);
}

// int				ft_lex_dollar(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	if ((*input)[*index] == '$')
// 	{
// 		if ((*current)->token != WORD)
// 		{
// 			if (ft_lex_newword(input, index, current, shell) == -1)
// 				return (-1);
// 		}
// 		else
// 			(*current)->len++;
// 		(*index)++;
// 		return (ft_lex_dollar_mode(input, index, current, shell));
// 	}
// 	return (1);
// }

// int				ft_lex_bquote_mode(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	int			i;
// 	int			ret;

// 	while ((*input)[*index] != '`')
// 	{
// 		if ((*input)[*index] == '\0'
// 			&& !(*input = ft_continue_line(*input, shell)))
// 			return (-1);
// 		i = 0;
// 		while (g_tokcond[i].sub_mode == 0 ||
// 			(ret = g_tokcond[i].cond(input, index, current, shell)) > 0)
// 			i++;
// 		if (ret == -1)
// 			return (-1);
// 		(*index)++;
// 	}
// 	(*current)->len++;
// 	return (0);
// }

int				ft_lex_bquote_mode(t_lex *lex, t_42sh *shell)
{
	int			i;
	int			ret;

	while (lex->input[lex->index] != '`')
	{
		if (lex->input[lex->index] == '\0')
		{
			if (ft_continue_line(lex, shell))
			{
				ft_putstr_fd(EOFWHILELOOK"``'\n", 2);
				return (-1);
			}
		}
		else
		{
			i = 0;
			while (g_tokcond[i].sub_mode == 0 ||
				(ret = g_tokcond[i].cond(lex, shell)) > 0)
				i++;
			if (ret == -1)
				return (-1);
		}
	}
	return (0);
}

int				ft_lex_bquote(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == '`')
	{
		ft_lex_word(lex, shell);
		if (ft_lex_bquote_mode(lex, shell))
			return (-1);
		ft_lex_word(lex, shell);
		return (0);
	}
	return (1);
}

// int				ft_lex_bquote(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	if ((*input)[*index] == '`')
// 	{
// 		if ((*current)->token != WORD)
// 		{
// 			if (ft_lex_newword(input, index, current, shell) == -1)
// 				return (-1);
// 		}
// 		else
// 			(*current)->len++;
// 		(*index)++;
// 		return (ft_lex_bquote_mode(input, index, current, shell));
// 	}
// 	return (1);
// }

int				ft_lex_ionumber(t_lex *lex, t_42sh *shell)
{
	size_t		i;

	(void)shell;
	if ((lex->input[lex->index] == '>' || lex->input[lex->index] == '<')
		&& lex->current && lex->current->token == WORD
		&& lex->current->len <= 10
		&& lex->index == lex->current->start + lex->current->len)
	{
		i = lex->current->start;
		while (i < lex->current->start + lex->current->len)
		{
			if (lex->input[i] < '0' || lex->input[i] > '9')
				return (1);
			i++;
		}
		if (lex->current->len == 10 && ft_strncmp(lex->input
			+ lex->current->start, "2147483647", 10) > 0)
			return (1);
		lex->current->token = IO_NUMBER;
	}
	return (1);
}

// int				ft_lex_ionumber(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	size_t		i;

// 	(void)shell;
// 	if (((*input)[*index] == '>' || (*input)[*index] == '<')
// 		&& (*current)->token == WORD && (*current)->len <= 10)
// 	{
// 		i = (*current)->start;
// 		while (i < (*current)->len)
// 		{
// 			if ((*input)[i] < '0' || (*input)[i] > '9')
// 				return (1);
// 			i++;
// 		}
// 		if ((*current)->len == 10 && ft_strncmp(*input + (*current)->start,
// 			"2147483647", 10) > 0)
// 			return (1);
// 		(*current)->token = IO_NUMBER;
// 	}
// 	return (1);
// }

int				ft_find_operator(t_lex *lex)
{
	int			i;
	int			op;

	i = 0;
	op = -1;
	while (g_toktab[i].str)
	{
		while (g_toktab[i].str && !ft_strnequ(g_toktab[i].str,
			lex->input + lex->index, ft_strlen(g_toktab[i].str)))
			i++;
		if (g_toktab[i].str && (op == -1
			|| ft_strlen(g_toktab[i].str) > ft_strlen(g_toktab[op].str)))
			op = i;
		if (g_toktab[i].str)
			i++;
	}
	return (op);
}

int				ft_lex_operator(t_lex *lex, t_42sh *shell)
{
	int			op;

	op = ft_find_operator(lex);
	if (op >= 0)
	{
		if (ft_lex_delimiter(lex, shell))
			return (0);
		ft_add_toklist(lex, g_toktab[op].token);
		lex->current->start = lex->index;
		lex->current->len = ft_strlen(g_toktab[op].str);
		lex->index = lex->index + lex->current->len;
		if (g_toktab[op].redir_op)
			lex->redir_op = true;
		else if (g_toktab[op].alias_recognition)
			lex->alias_recognition = true;
		return (0);
	}
	return (1);
}

// int				ft_lex_newoperator(char **input, size_t *index,
// 				t_toklist **current, t_42sh *shell)
// {
// 	int			i;

// 	(void)shell;
// 	i = 0;
// 	while (g_toktab[i].str && g_toktab[i].str[0] != (*input)[*index])
// 		i++;
// 	if (g_toktab[i].str)
// 	{
// 		if ((*current)->token != NONE)
// 		{
// 			if (!((*current)->next = ft_newtoklist()))
// 				return (-1);
// 			*current = (*current)->next;
// 		}
// 		(*current)->token = OPP;
// 		(*current)->start = *index;
// 		(*current)->len = 1;
// 		return (0);
// 	}
// 	return (1);
// }

int				ft_lex_blank(t_lex *lex, t_42sh *shell)
{
	if (lex->input[lex->index] == ' ' || lex->input[lex->index] == '\t')
	{
		if (ft_lex_delimiter(lex, shell))
			return (0);
		lex->index++;
		return (0);
	}
	return (1);
}

// int				ft_lex_blank(char **input, size_t *index, t_toklist **current, t_42sh *shell)
// {
// 	(void)shell;
// 	if ((*input)[*index] == ' ' || (*input)[*index] == '\t')
// 	{
// 		if ((*current)->token != NONE)
// 		{
// 			if (!((*current)->next = ft_newtoklist()))
// 				return (-1);
// 			*current = (*current)->next;
// 		}
// 		return (0);
// 	}
// 	return (1);
// }

int				ft_lex_sharp(t_lex *lex, t_42sh *shell)
{
	(void)shell;
	if (lex->input[lex->index] == '#' && (!(lex->current)
		|| lex->index != lex->current->start + lex->current->len))
	{
		while (lex->input[lex->index] && lex->input[lex->index] != '\n')
			lex->index++;
		return (0);
	}
	return (1);
}

// int				ft_lex_sharp(char **input, size_t *index, t_toklist **current, t_42sh *shell)
// {
// 	(void)shell;
// 	if ((*current)->token == NONE && (*input)[*index] == '#')
// 	{
// 		while ((*input)[*index + 1] != '\n')
// 			(*index)++;
// 		return (0);
// 	}
// 	return (1);
// }

int				ft_lex_word(t_lex *lex, t_42sh *shell)
{
	(void)shell;
	if (!lex->current || lex->current->token != WORD
		|| lex->index != lex->current->start + lex->current->len)
	{
		ft_add_toklist(lex, WORD);
		lex->current->start = lex->index;
	}
	lex->current->len++;
	lex->index++;
	return (0);
}

// int				ft_lex_word(char **input, size_t *index, t_toklist **current, t_42sh *shell)
// {
// 	(void)input;
// 	(void)index;
// 	(void)shell;
// 	if ((*current)->token == WORD)
// 	{
// 		(*current)->len++;
// 		return (0);
// 	}
// 	return (1);
// }

// int				ft_lex_newword(char **input, size_t *index, t_toklist **current, t_42sh *shell)
// {
// 	(void)input;
// 	(void)shell;
// 	if ((*current)->token != NONE)
// 	{
// 		if (!((*current)->next = ft_newtoklist()))
// 			return (-1);
// 		*current = (*current)->next;
// 	}
// 	(*current)->token = WORD;
// 	(*current)->start = *index;
// 	(*current)->len = 1;
// 	(*index)++;
// 	return (0);
// }

void			ft_print_toklist(char *input, t_toklist *list)
{
	while (list)
	{
		ft_putendl(g_tokstr[list->token]);
		ft_putnbr(list->start);
		ft_putchar('\n');
		ft_putnbr(list->len);
		ft_putchar('\n');
		write(1, input + list->start, list->len);
		ft_putchar('\n');
		ft_putstr("----------------------------------------\n");
		list = list->next;
	}
}

int				ft_lexer(t_lex *lex, t_42sh *shell)
{
	int			i;
	int			ret;

	while (lex->input[lex->index])
	{
		i = 0;
		while ((ret = g_tokcond[i].cond(lex, shell)) > 0)
			i++;
		if (ret == -1)
			return (-1);
		if (lex->input[lex->index] == '\0')
			ft_lex_delimiter(lex, shell);
	}
	// ft_print_toklist(lex->input, lex->begin);
	return (0);
}
