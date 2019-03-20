/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 01:47:25 by geargenc          #+#    #+#             */
/*   Updated: 2019/03/20 02:44:41 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_toklist		*ft_newtoklist(void)
{
	t_toklist	*new;

	if (!(new = (t_toklist *)malloc(sizeof(t_toklist))))
		return (NULL);
	ft_bzero(new, sizeof(t_toklist));
	return (new);
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
	if (!(join = (char *)malloc(i + j + 1)))
		return (NULL);
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

char			*ft_continue_line(char *current, t_42sh *shell)
{
	if (isatty(STDIN_FILENO))
	{
		ft_putstr("> ");
		shell->prompt_len = 2;
	}
	if (get_line(shell) != 1)
		return (NULL);
	return ((shell->stdin->input = ft_strjoinfree(current,
		shell->stdin->input, 3)));
}

int				ft_lex_newline(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	(void)shell;
	if ((*input)[*index] == '\n')
	{
		if ((*current)->token != NONE)
		{
			if (!((*current)->next = ft_newtoklist()))
				return (-1);
			*current = (*current)->next;
		}
		(*current)->token = NEWLINE;
		(*current)->start = *index;
		(*current)->len = 1;
		return (0);
	}
	return (1);
}

int				ft_lex_operator(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	size_t		i;
	size_t		j;

	(void)shell;
	if ((*current)->token == OPP)
	{
		i = 0;
		while (g_toktab[i].str)
		{
			j = 0;
			while (j < (*current)->len && g_toktab[i].str[j] ==
				(*input)[(*current)->start + j])
				j++;
			if (j == (*current)->len && g_toktab[i].str[j] ==
				(*input)[*index])
			{
				(*current)->len++;
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int				ft_lex_notoperator(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	size_t		i;
	size_t		j;

	(void)index;
	(void)shell;
	if ((*current)->token == OPP)
	{
		i = 0;
		while (g_toktab[i].str)
		{
			j = 0;
			while (j < (*current)->len && g_toktab[i].str[j] ==
				(*input)[(*current)->start + j])
				j++;
			if (j == (*current)->len && g_toktab[i].str[j] == '\0')
			{
				(*current)->token = g_toktab[i].token;
				if (!((*current)->next = ft_newtoklist()))
					return (-1);
				*current = (*current)->next;
				return (1);
			}
			i++;
		}
	}
	return (1);
}

int				ft_lex_backslash(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	(void)shell;
	if ((*input)[*index] == '\\')
	{
		if ((*current)->token != WORD)
		{
			if (ft_lex_newword(input, index, current, shell) == -1)
				return (-1);
		}
		else
			(*current)->len++;
		(*current)->len++;
		(*index)++;
		return (0);
	}
	return (1);
}

int				ft_lex_quote(char **input, size_t *index, t_toklist **current, t_42sh *shell)
{
	if ((*input)[*index] == '\'')
	{
		if ((*current)->token != WORD)
		{
			if (ft_lex_newword(input, index, current, shell) == -1)
				return (-1);
		}
		else
			(*current)->len++;
		(*index)++;
		(*current)->len++;
		while ((*input)[*index] != '\'')
		{
			if ((*input)[*index] == '\0')
			{
				if (!(*input = ft_continue_line(*input, shell)))
					return (-1);
			}
			else
			{
				(*current)->len++;
				(*index)++;
			}
		}
		return (0);
	}
	return (1);
}

int				ft_lex_dquote_mode(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	int			i;
	int			ret;

	while ((*input)[*index] != '\"')
	{
		if ((*input)[*index] == '\0')
		{
			if (!(*input = ft_continue_line(*input, shell)))
				return (-1);
		}
		else
		{
			i = 0;
			while (g_tokcond[i].dquote_mode == 0 ||
				(ret = g_tokcond[i].cond(input, index, current, shell)) > 0)
				i++;
			if (ret == -1)
				return (-1);
			(*index)++;
		}
	}
	(*current)->len++;
	return (0);
}

int				ft_lex_dquote(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	if ((*input)[*index] == '\"')
	{
		if ((*current)->token != WORD)
		{
			if (ft_lex_newword(input, index, current, shell) == -1)
				return (-1);
		}
		else
			(*current)->len++;
		(*index)++;
		return (ft_lex_dquote_mode(input, index, current, shell));
	}
	return (1);
}

int				ft_lex_dollar_brace(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	size_t		i;
	int			braces;
	int			ret;

	braces = 1;
	while (braces)
	{
		(*index)++;
		if ((*input)[*index] == '\0'
			&& !(*input = ft_continue_line(*input, shell)))
			return (-1);
		if ((*input)[*index] == '{')
			braces++;
		else if ((*input)[*index] == '}')
			braces--;
		i = 0;
		while (g_tokcond[i].sub_mode == 0 ||
			(ret = g_tokcond[i].cond(input, index, current, shell)) > 0)
			i++;
		if (ret == -1)
			return (-1);
	}
	return (0);
}

int				ft_lex_dollar_par(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	size_t		i;
	int			pars;
	int			ret;

	pars = 1;
	while (pars)
	{
		(*index)++;
		if ((*input)[*index] == '\0'
			&& !(*input = ft_continue_line(*input, shell)))
			return (-1);
		if ((*input)[*index] == '(')
			pars++;
		else if ((*input)[*index] == ')')
			pars--;
		i = 0;
		while (g_tokcond[i].sub_mode == 0 ||
			(ret = g_tokcond[i].cond(input, index, current, shell)) > 0)
			i++;
		if (ret == -1)
			return (-1);
	}
	return (0);
}

int				ft_lex_dollar_mode(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	if ((*input)[*index] == '{')
	{
		(*current)->len++;
		return (ft_lex_dollar_brace(input, index, current, shell));
	}
	else if ((*input)[*index] == '(')
	{
		(*current)->len++;
		return (ft_lex_dollar_par(input, index, current, shell));
	}
	(*index)--;
	return (0);
}

int				ft_lex_dollar(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	if ((*input)[*index] == '$')
	{
		if ((*current)->token != WORD)
		{
			if (ft_lex_newword(input, index, current, shell) == -1)
				return (-1);
		}
		else
			(*current)->len++;
		(*index)++;
		return (ft_lex_dollar_mode(input, index, current, shell));
	}
	return (1);
}

int				ft_lex_bquote_mode(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	int			i;
	int			ret;

	while ((*input)[*index] != '`')
	{
		if ((*input)[*index] == '\0'
			&& !(*input = ft_continue_line(*input, shell)))
			return (-1);
		i = 0;
		while (g_tokcond[i].sub_mode == 0 ||
			(ret = g_tokcond[i].cond(input, index, current, shell)) > 0)
			i++;
		if (ret == -1)
			return (-1);
		(*index)++;
	}
	(*current)->len++;
	return (0);
}

int				ft_lex_bquote(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	if ((*input)[*index] == '`')
	{
		if ((*current)->token != WORD)
		{
			if (ft_lex_newword(input, index, current, shell) == -1)
				return (-1);
		}
		else
			(*current)->len++;
		(*index)++;
		return (ft_lex_bquote_mode(input, index, current, shell));
	}
	return (1);
}

int				ft_lex_ionumber(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	size_t		i;

	(void)shell;
	if (((*input)[*index] == '>' || (*input)[*index] == '<')
		&& (*current)->token == WORD && (*current)->len <= 10)
	{
		i = (*current)->start;
		while (i < (*current)->len)
		{
			if ((*input)[i] < '0' || (*input)[i] > '9')
				return (1);
			i++;
		}
		if ((*current)->len == 10 && ft_strncmp(*input + (*current)->start,
			"2147483647", 10) > 0)
			return (1);
		(*current)->token = IO_NUMBER;
	}
	return (1);
}

int				ft_lex_newoperator(char **input, size_t *index,
				t_toklist **current, t_42sh *shell)
{
	int			i;

	(void)shell;
	i = 0;
	while (g_toktab[i].str && g_toktab[i].str[0] != (*input)[*index])
		i++;
	if (g_toktab[i].str)
	{
		if ((*current)->token != NONE)
		{
			if (!((*current)->next = ft_newtoklist()))
				return (-1);
			*current = (*current)->next;
		}
		(*current)->token = OPP;
		(*current)->start = *index;
		(*current)->len = 1;
		return (0);
	}
	return (1);
}

int				ft_lex_blank(char **input, size_t *index, t_toklist **current, t_42sh *shell)
{
	(void)shell;
	if ((*input)[*index] == ' ' || (*input)[*index] == '\t')
	{
		if ((*current)->token != NONE)
		{
			if (!((*current)->next = ft_newtoklist()))
				return (-1);
			*current = (*current)->next;
		}
		return (0);
	}
	return (1);
}

int				ft_lex_sharp(char **input, size_t *index, t_toklist **current, t_42sh *shell)
{
	(void)shell;
	if ((*current)->token == NONE && (*input)[*index] == '#')
	{
		while ((*input)[*index + 1] != '\n')
			(*index)++;
		return (0);
	}
	return (1);
}

int				ft_lex_word(char **input, size_t *index, t_toklist **current, t_42sh *shell)
{
	(void)input;
	(void)index;
	(void)shell;
	if ((*current)->token == WORD)
	{
		(*current)->len++;
		return (0);
	}
	return (1);
}

int				ft_lex_newword(char **input, size_t *index, t_toklist **current, t_42sh *shell)
{
	(void)input;
	(void)shell;
	if ((*current)->token != NONE)
	{
		if (!((*current)->next = ft_newtoklist()))
			return (-1);
		*current = (*current)->next;
	}
	(*current)->token = WORD;
	(*current)->start = *index;
	(*current)->len = 1;
	return (0);
}

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

t_toklist		*ft_lexer(char **input, t_42sh *shell)
{
	size_t		index;
	t_toklist	*begin;
	t_toklist	*current;
	int			i;
	int			ret;

	index = 0;
	if (!(begin = ft_newtoklist()))
		return (NULL);
	current = begin;
	while ((*input)[index])
	{
		i = 0;
		while ((ret = g_tokcond[i].cond(input, &index, &current, shell)) > 0)
			i++;
		if (ret == -1)
			return (NULL);
		index++;
	}
	if (current->token == NONE)
		free(current);
	// ft_print_toklist(*input, begin);
	return (begin);
}
