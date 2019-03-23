/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:26:39 by geargenc          #+#    #+#             */
/*   Updated: 2019/03/23 03:56:06 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		**ft_init_args(t_node *current)
{
	char	**args;
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = current;
	while ((tmp = tmp->right))
		i++;
	args = (char **)ft_malloc_exit((i + 1) * sizeof(char *));
	i = 0;
	tmp = current;
	while ((tmp = tmp->right))
	{
		if (!(args[i] = ft_strdup(tmp->data)))
			exit(2);
		i++;
	}
	args[i] = NULL;
	return (args);
}

typedef enum			e_txttype
{
	TXT_NONE = 0,
	TEXT,
	TILDE,
	VAR,
	BRACE_VAR,
	CMD_SUB,
	CMD_SUB_BQUOTE,
	ARTH_EXPR
}						t_txttype;

typedef struct			s_txtlist
{
	t_txttype			token;
	char				*data;
	size_t				start;
	size_t				len;
	int					dquote;
	struct s_txtlist	*next;
}						t_txtlist;

t_txtlist		*ft_new_txtlist(void)
{
	t_txtlist	*new;

	if (!(new = (t_txtlist *)ft_malloc_exit(sizeof(t_txtlist))))
		return (NULL);
	new->token = TXT_NONE;
	new->data = NULL;
	new->start = 0;
	new->len = 0;
	new->dquote = 0;
	new->next = NULL;
	return (new);
}

t_txtlist		*ft_add_txtlist(char *data, t_txttype token, t_txtlist **to)
{
	if ((*to)->token != TXT_NONE)
	{
		if (!((*to)->next = ft_new_txtlist()))
			return (NULL);
		*to = (*to)->next;
	}
	(*to)->data = data;
	(*to)->token = token;
	return (*to);
}

int			ft_parse_tilde(char *word, size_t *index,
			t_txtlist **current, int *dquote)
{
	if (word[*index] == '~' && !(*dquote) && (*index == 0
		|| word[*index - 1] == ' ' || word[*index - 1] == '\n'
		|| word[*index - 1] == '\t' || word[*index - 1] == ':'))
	{
		ft_add_txtlist(word, TILDE, current);
		(*current)->start = *index;
		(*index)++;
		if (word[*index] == '+' || word[*index] == '-')
			(*index)++;
		else if (ft_isalpha(word[*index]) || word[*index] == '_')
			while (ft_isalnum(word[*index]) || word[*index] == '_')
				(*index)++;
		(*current)->len = *index - (*current)->start;
		return (0);
	}
	return (1);
}

int			ft_parse_brace_var(char *word, size_t *index, t_txtlist **current)
{
	int		braces;

	(*current)->token = BRACE_VAR;
	(*index)++;
	braces = 1;
	while (braces)
	{
		if (word[*index] == '\0')
			return (-1);
		else if (word[*index] == '{')
			braces++;
		else if (word[*index] == '}')
			braces--;
		else if (word[*index] == '\\')
			(*index)++;
		(*index)++;
	}
	return (0);
}

int			ft_parse_cmd_sub(char *word, size_t *index, t_txtlist **current)
{
	int		pars;

	(*index)++;
	pars = 1;
	(*current)->token = word[*index] == '(' ? ARTH_EXPR : CMD_SUB;
	while (pars)
	{
		if (word[*index] == '\0')
			return (-1);
		else if (word[*index] == '(')
			pars++;
		else if (word[*index] == ')' && word[(*index) + 1] == ')'
			&& (*current)->token == ARTH_EXPR && pars == 2)
		{
			(*index) += 2;
			return (0);
		}
		else if (word[*index] == ')')
			pars--;
		else if (word[*index] == '\\')
			(*index)++;
		(*index)++;
	}
	(*current)->token = CMD_SUB;
	return (0);
}

int			ft_parse_var(char *word, size_t *index,
			t_txtlist **current, int *dquote)
{
	int		ret;

	if (word[*index] == '$')
	{
		ret = 0;
		ft_add_txtlist(word, VAR, current);
		(*current)->start = *index;
		(*current)->dquote = *dquote;
		(*index)++;
		if (word[*index] == '$' || word[*index] == '?' || word[*index] == '!')
			(*index)++;
		else if (ft_isalpha(word[*index]) ||  word[*index] == '_')
			while (ft_isalnum(word[*index]) || word[*index] == '_')
				(*index)++;
		else if (word[*index] == '{')
			ret = ft_parse_brace_var(word, index, current);
		else if (word[*index] == '(')
			ret = ft_parse_cmd_sub(word, index, current);
		(*current)->len = *index - (*current)->start;
		return (ret);
	}
	return (1);
}

int			ft_parse_text(char *word, size_t *index,
			t_txtlist **current, int *dquote)
{
	if (word[*index] == '"')
		*dquote = !(*dquote);
	if ((*current)->token != TEXT)
	{
		ft_add_txtlist(word, TEXT, current);
		(*current)->start = *index;
	}
	(*current)->len++;
	(*index)++;
	return (0);
}

int			ft_parse_backslash(char *word, size_t *index,
			t_txtlist **current, int *dquote)
{
	if (word[*index] == '\\')
	{
		ft_parse_text(word, index, current, dquote);
		if (word[*index] == '\0')
			return (-1);
		(*index)++;
		(*current)->len = *index - (*current)->start;
		return (0);
	}
	return (1);
}

int			ft_parse_quote(char *word, size_t *index,
			t_txtlist **current, int *dquote)
{
	if (word[*index] == '\'' && !(*dquote))
	{
		ft_parse_text(word, index, current, dquote);
		while (word[*index] != '\'')
		{
			if (word[*index] == '\0')
				return (-1);
			(*index)++;
		}
		(*index)++;
		(*current)->len = *index - (*current)->start;
		return (0);
	}
	return (1);
}

int			ft_parse_bquote(char *word, size_t *index,
			t_txtlist **current, int *dquote)
{
	(void)dquote;
	if (word[*index] == '`')
	{
		ft_add_txtlist(word, CMD_SUB_BQUOTE, current);
		(*current)->start = *index;
		(*index)++;
		while (word[*index] != '`')
		{
			if (word[*index] == '\0')
				return (-1);
			else if (word[*index] == '\\')
				(*index)++;
			(*index)++;
		}
		(*index)++;
		(*current)->len = *index - (*current)->start;
		return (0);
	}
	return (1);
}

int			(*g_txttab[])(char *word, size_t *index,
			t_txtlist **current, int *dquote) =
{
	&ft_parse_tilde,
	&ft_parse_var,
	&ft_parse_bquote,
	&ft_parse_backslash,
	&ft_parse_quote,
	&ft_parse_text
};

void			ft_parse_error(t_txtlist *list)
{
	t_txtlist	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	ft_putstr_fd("42sh: unexpected '\\0'\n", 2);
}

t_txtlist		*ft_parse_word(char *word)
{
	t_txtlist	*list[2];
	size_t		index;
	int			dquote;
	int			i;
	int			ret;

	if (!(list[0] = ft_new_txtlist()))
		return (NULL);
	list[1] = list[0];
	index = 0;
	dquote = 0;
	while (word[index])
	{
		i = 0;
		while ((ret = g_txttab[i](word, &index, &(list[1]), &dquote)) == 1)
			i++;
		if (ret < 0)
		{
			ft_parse_error(list[0]);
			return (NULL);
		}
	}
	return (list[0]);
}

char			*g_txtstr[] =
{
	"TXT_NONE",
	"TEXT",
	"TILDE",
	"VAR",
	"BRACE_VAR",
	"CMD_SUB",
	"CMD_SUB_BQUOTE",
	"ARTH_EXPR"
};

void			ft_print_txtlist(char *input, t_txtlist *list)
{
	while (list)
	{
		ft_putstr("[");
		ft_putstr(g_txtstr[list->token]);
		ft_putchar('-');
		ft_putnbr(list->start);
		ft_putchar('-');
		ft_putnbr(list->len);
		ft_putchar('-');
		write(1, input + list->start, list->len);
		ft_putchar(']');
		list = list->next;
	}
	ft_putchar('\n');
}

char			*ft_expanse_word(char *word, t_42sh *shell)
{
	t_txtlist	*list;
	char		*result;

	(void)shell;
	(void)result;
	if (!(list = ft_parse_word(word)))
		return (NULL);
	ft_print_txtlist(word, list);
	return (word);
}

char		**ft_expanse_args(char **args, t_42sh *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	while (args[i])
	{
		tmp = args[i];
		if (!(args[i] = ft_expanse_word(args[i], shell)))
			exit(2);
		// free(tmp);
		i++;
	}
	return (args);
}

char		**ft_command_to_args(t_node *current, t_42sh *shell)
{
	char	**args;

	args = ft_init_args(current);
	ft_expanse_args(args, shell);
	// args = ft_split_args(args, shell);
	// ft_rmquotes_args(args, shell);
	return (args);
}
