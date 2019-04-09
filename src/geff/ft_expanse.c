/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:26:39 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/09 05:36:42 by jolabour         ###   ########.fr       */
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

char		*ft_spparam_dollar(t_42sh *shell)
{
	return (ft_itoa(shell->pid));
}

char		*ft_spparam_qmark(t_42sh *shell)
{
	return (ft_itoa(shell->retval));
}

char		*ft_spparam_bang(t_42sh *shell)
{
	return (ft_itoa(shell->last_bg));
}

char		*ft_spparam_zero(t_42sh *shell)
{
	if (shell->args[0])
		return (ft_strdup(shell->args[0]));
	return (ft_strdup("42sh"));
}

char		*(*ft_get_spparam(char c))(t_42sh *)
{
	int		i;

	i = 0;
	while (g_spparamtab[i].c && g_spparamtab[i].c != c)
		i++;
	return (g_spparamtab[i].f);
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
		if (ft_get_spparam(word[*index]))
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

t_txtlist		*ft_parse_check(t_txtlist *list)
{
	if (list->token)
		return (list);
	free(list);
	return (NULL);
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
	return (ft_parse_check(list[0]));
}

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

int			ft_exp_text(t_txtlist *txt, t_42sh *shell)
{
	(void)shell;
	txt->data = ft_strsub(txt->data, txt->start, txt->len);
	return (0);
}

char		*ft_getvar(char *var, t_42sh *shell)
{
	void	*ptr;
	char	*varenv;

	ptr = ft_get_spparam(*var);
	if (ptr)
		return (((char *(*)(t_42sh *))ptr)(shell));
	varenv = ft_strjoin(var, "=");
	ptr = ft_getenv(shell->env, varenv, ft_strlen(varenv), NULL);
	free(varenv);
	if (ptr)
		return (ft_strdup(ptr));
	ptr = get_var(shell, var);
	if (ptr)
		return ((char *)ptr);
	return (NULL);
}

char				*ft_tilde_alone(t_42sh *shell)
{
	char			*path;
	struct passwd	*pw;

	path = ft_getvar("HOME", shell);
	if (!path)
	{
		pw = getpwuid(getuid());
		if (pw)
			path = ft_strdup(pw->pw_dir);
	}
	return (path);
}

char				*ft_tilde_user(t_txtlist *txt)
{
	char			*user;
	struct passwd	*pw;

	user = ft_strsub(txt->data, txt->start + 1, txt->len - 1);
	if (user)
	{
		pw = getpwnam(user);
		free(user);
		if (pw)
			return (ft_strdup(pw->pw_dir));
	}
	return (NULL);
}

int			ft_exp_tilde(t_txtlist *txt, t_42sh *shell)
{
	char	*res;

	if (txt->data[txt->start + txt->len]
		&& txt->data[txt->start + txt->len] != '/'
		&& txt->data[txt->start + txt->len] != ':')
		return (ft_exp_text(txt, shell));
	if (txt->len == 1)
		res = ft_tilde_alone(shell);
	else if (txt->data[txt->start + 1] == '+')
		res = ft_getvar("PWD", shell);
	else if (txt->data[txt->start + 1] == '-')
		res = ft_getvar("OLDPWD", shell);
	else
		res = ft_tilde_user(txt);
	if (!res)
		return (ft_exp_text(txt, shell));
	txt->data = res;
	return (0);
}

int			ft_count_quotes(char *word)
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (word[i])
	{
		if (word[i] == '\\' || word[i] == '\"' || word[i] == '\'')
			quotes++;
		i++;
	}
	return (quotes);
}

char		*ft_backslash_quotes(char *word)
{
	char	*res;
	int		i;
	int		quotes;

	quotes = ft_count_quotes(word);
	if (!quotes)
		return (word);
	res = (char *)ft_malloc_exit((ft_strlen(word) + quotes + 1) * sizeof(char));
	i = 0;
	quotes = 0;
	while (word[i])
	{
		if (word[i] == '\\' || word[i] == '\"' || word[i] == '\'')
		{
			res[i + quotes] = '\\';
			quotes++;
		}
		res[i + quotes] = word[i];
		i++;
	}
	res[i + quotes] = '\0';
	free(word);
	return (res);
}

int			ft_exp_var(t_txtlist *txt, t_42sh *shell)
{
	char	*var;

	if (txt->len == 1)
		return (ft_exp_text(txt, shell));
	var = ft_strsub(txt->data, txt->start + 1, txt->len - 1);
	txt->data = ft_getvar(var, shell);
	free(var);
	txt->data = txt->data ? ft_backslash_quotes(txt->data) : ft_strdup("");
	return (0);
}

int			ft_exp_brace_error(t_txtlist *txt, char *var)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	write(STDERR_FILENO, txt->data + txt->start, txt->len);
	ft_putstr_fd(": bad substitution\n", STDERR_FILENO);
	if (var)
		free(var);
	return (-1);
}

int			ft_exp_brace(t_txtlist *txt, t_42sh *shell)
{
	char	*var;
	char	*res;
	int		i;

	var = NULL;
	i = 0;
	if (txt->len < 4)
		return (ft_exp_brace_error(txt, NULL));
	if (ft_get_spparam(txt->data[2]))
		var = ft_strsub(txt->data, txt->start + 2, (i = 1));
	else if (ft_isalpha(txt->data[txt->start + 2])
		|| txt->data[txt->start + 2] == '_')
	{
		while (ft_isalnum(txt->data[txt->start + i + 2])
			|| txt->data[txt->start + i + 2] == '_')
			i++;
		var = ft_strsub(txt->data, txt->start + 2, i);
	}
	if ((unsigned int)i + 3 != txt->len || !var)
		return (ft_exp_brace_error(txt, var));
	res = var ? ft_getvar(var, shell) : NULL;
	free(var);
	txt->data = res ? ft_backslash_quotes(res) : ft_strdup("");
	return (0);
}

int			ft_cmdsub_child(int pipefd[2], t_node *ast, t_42sh *shell)
{
	close(pipefd[0]);
	shell->pgid = getpgrp();
	if (pipefd[1] != STDOUT_FILENO)
	{
		ft_dup2_exit(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (ast)
		g_exetab[ast->token](ast, shell);
	exit(EXIT_SUCCESS);
}

char		*ft_del_ending_newlines(char *str)
{
	size_t	i;
	size_t	last;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			last = i;
			while (str[i] == '\n')
				i++;
			if (!str[i])
				str[last] = '\0';
		}
		else
			i++;
	}
	return (str);
}

void		ft_cmdsub_error(char *command)
{
	ft_putstr_fd("42sh: command substitution: `", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd("\'\n", STDERR_FILENO);
}

char		*ft_cmdsub_read(int fd)
{
	char	*sub;
	char	buf[BUFF_SIZE + 1];
	int		ret;

	sub = ft_strdup("");
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		sub = ft_strjoinfree(sub, buf, 1);
	}
	ft_del_ending_newlines(sub);
	close(fd);
	return (sub);
}

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

char		*ft_cmdsub(char *command, t_42sh *shell)
{
	t_ast	ast;
	int		pipefd[2];
	pid_t	pid;
	char	*result;

	ast = (t_ast){NULL, NULL, NULL};
	result = NULL;
	if (ft_cmdsub_parse(&ast, command, shell))
		ft_cmdsub_error(command);
	else
	{
		ft_pipe_exit(pipefd);
		pid = ft_fork_exit();
		if (pid == 0)
			ft_cmdsub_child(pipefd, ast.begin, shell);
		close(pipefd[1]);
		result = ft_cmdsub_read(pipefd[0]);
		ft_ast_free(ast.begin);
	}
	free(command);
	return (result ? ft_backslash_quotes(result) : NULL);
}

int			ft_exp_sub(t_txtlist *txt, t_42sh *shell)
{
	if (!(txt->data = ft_cmdsub(ft_strsub(txt->data, txt->start + 2,
		txt->len - 3), shell)))
		return (-1);
	return (0);
}

int			ft_exp_bquote(t_txtlist *txt, t_42sh *shell)
{
	if (!(txt->data = ft_cmdsub(ft_strsub(txt->data, txt->start + 1,
		txt->len - 2), shell)))
		return (-1);
	return (0);
}

int			ft_exp_expr(t_txtlist *txt, t_42sh *shell)
{
	(void)shell;
	txt->data = ft_strsub(txt->data, txt->start, txt->len);
	return (0);
}

int				ft_exp_error(t_txtlist *list, t_txtlist *error)
{
	t_txtlist	*tmp;

	while (list != error)
	{
		tmp = list;
		list = list->next;
		free(tmp->data);
		free(tmp);
	}
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	return (-1);
}

int				ft_exp(t_txtlist *list, t_42sh *shell)
{
	t_txtlist	*tmp;

	tmp = list;
	while (tmp)
	{
		if (g_exptab[tmp->token](tmp, shell))
			return (ft_exp_error(list, tmp));
		tmp = tmp->next;
	}
	return (0);
}

size_t			ft_txt_len(t_txtlist *list)
{
	size_t		count;

	count = 0;
	while (list)
	{
		
		list->len = ft_strlen(list->data);
		count = count + list->len;
		list = list->next;
	}
	return (count);
}

char			*ft_txt_join(t_txtlist *list)
{
	t_txtlist	*tmp;
	char		*word;
	size_t		size;

	word = (char *)ft_malloc_exit((ft_txt_len(list) + 1) * sizeof(char));
	word[0] = '\0';
	size = 0;
	while (list)
	{
		ft_strcpy(word + size, list->data);
		size = size + list->len;
		tmp = list;
		list = list->next;
		free(tmp->data);
		free(tmp);
	}
	return (word);
}

char			*ft_expanse_word(char *word, t_42sh *shell)
{
	t_txtlist	*list;
	char		*result;

	list = ft_parse_word(word);
	if (ft_exp(list, shell))
	{
		shell->stopexe = true;
		return (NULL);
	}
	result = ft_txt_join(list);
	return (result);
}

char		**ft_exp_args_error(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	i++;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (NULL);
}

char		**ft_expanse_args(char **args, t_42sh *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	while (args[i])
	{
		tmp = args[i];
		args[i] = ft_expanse_word(args[i], shell);
		free(tmp);
		if (!args[i])
			return (ft_exp_args_error(args));
		i++;
	}
	return (args);
}

void		ft_rmquotes_word(char *word)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (word[i])
	{
		if (word[i] == '\\' && quote != '\'')
		{
			ft_strcpy(word + i, word + i + 1);
			i++;
		}
		else if (word[i] == '\"' && quote != '\'')
		{
			ft_strcpy(word + i, word + i + 1);
			quote = (quote == '\"') ? 0 : '\"';
		}
		else if (word[i] == '\'' && quote != '\"')
		{
			ft_strcpy(word + i, word + i + 1);
			quote = (quote == '\'') ? 0 : '\'';
		}
		else
			i++;
	}
}

void		ft_rmquotes_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		ft_rmquotes_word(args[i]);
		i++;
	}
}

size_t		ft_count_field_size(char *word, char *sep)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (word[i] && (quote || !ft_strchr(sep, word[i])))
	{
		if (word[i] == '\\' && quote != '\'' && word[i + 1])
			i++;
		else if (word[i] == '\"' && quote != '\'')
			quote = quote ? 0 : '\"';
		else if (word[i] == '\'' && quote != '\"')
			quote = quote ? 0 : '\'';
		i++;
	}
	return (i);
}

int			ft_count_fields(char *word, char *sep)
{
	size_t	i;
	int		fields;

	i = 0;
	fields = 0;
	while (word[i])
	{
		while (word[i] && ft_strchr(sep, word[i]))
			i++;
		if (word[i])
		{
			fields++;
			i = i + ft_count_field_size(word + i, sep);
		}
	}
	return (fields);
}

char		**ft_field_split_word(char *word, char *sep)
{
	char	**split;
	int		i;
	int		fields;
	size_t	field_size;

	split = (char **)ft_malloc_exit((ft_count_fields(word, sep) + 1)
		* sizeof(char *));
	i = 0;
	fields = 0;
	while (word[i])
	{
		while (word[i] && ft_strchr(sep, word[i]))
			i++;
		if (word[i])
		{
			field_size = ft_count_field_size(word + i, sep);
			split[fields] = ft_strsub(word, i, field_size);
			i = i + field_size;
			fields++;
		}
	}
	split[fields] = NULL;
	return (split);
}

int			ft_count_args(char ***splits)
{
	int		size;
	int		i;
	int		j;

	size = 0;
	j = 0;
	while (splits[j])
	{
		i = 0;
		while (splits[j][i])
		{
			i++;
			size++;
		}
		j++;
	}
	return (size);
}

char		**ft_gather_splits(char ***splits)
{
	char	**args;
	int		size;
	int		i;
	int		j;

	args = (char **)ft_malloc_exit((ft_count_args(splits) + 1)
		* sizeof(char *));
	size = 0;
	j = 0;
	while (splits[j])
	{
		i = 0;
		while (splits[j][i])
		{
			args[size] = splits[j][i];
			i++;
			size++;
		}
		free(splits[j]);
		j++;
	}
	args[size] = NULL;
	free(splits);
	return (args);
}

char		**ft_field_split(char **args, t_42sh *shell)
{
	char	***splits;
	char	*sep;
	int		i;

	i = 0;
	while (args[i])
		i++;
	splits = (char ***)ft_malloc_exit((i + 1) * sizeof(char **));
	sep = ft_getvar("IFS", shell);
	if (!sep)
		sep = ft_strdup(" \t\n");
	i = 0;
	while (args[i])
	{
		splits[i] = ft_field_split_word(args[i], sep);
		free(args[i]);
		i++;
	}
	splits[i] = NULL;
	free(args);
	free(sep);
	return (ft_gather_splits(splits));
}

char		**ft_command_to_args(t_node *current, t_42sh *shell)
{
	char	**args;

	args = ft_init_args(current);
	if (!ft_expanse_args(args, shell))
		return (NULL);
	args = ft_field_split(args, shell);
	ft_rmquotes_args(args);
	return (args);
}

char		*ft_simple_expanse(char *word, t_42sh *shell)
{
	char	*new;

	if ((new = ft_expanse_word(word, shell)))
		ft_rmquotes_word(new);
	return (new);
}
