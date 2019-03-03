/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 22:54:23 by jolabour          #+#    #+#             */
/*   Updated: 2019/01/24 04:30:10 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*get_var(t_42sh *sh, char *str)
{
	char		*substitute;
	int			i;
	t_var		*tmp;

	i = 0;
	tmp = sh->var->begin;
	while (i < sh->var->size)
	{
		if (ft_strequ(tmp->to_sub, str) == 1)
		{
			substitute = ft_strdup(tmp->sub);
			return (substitute);
		}
		tmp = tmp->next;
		i++;
	}
	substitute = ft_strdup("\0");
	return (substitute);
}

char			*substitute_param(t_42sh *sh, char *str, int *pos)
{
	char		*substitute;
	char		*to_search;
	int			save_pos;

	if (str[*pos] == '?')
	{
		if (str[*pos + 1] == '}')
		{
			substitute = ft_itoa(sh->argv->error_code);
			*pos = *pos + 1;
			return (substitute);
		}
		else
			return (NULL);
	}
	if (ft_isalpha(str[*pos]) == 1)
	{
		save_pos = *pos;
		*pos = *pos + 1;
		while (str[*pos])
		{
			if (ft_isalnum(str[*pos]) != 1)
			{
				if (str[*pos] == '}')
				{
					to_search = ft_strsub(str, save_pos, *pos - save_pos);
					substitute = get_var(sh, to_search);
					if (ft_strequ(substitute, "\0") == 1)
					{
						free(substitute);
						if ((substitute = ft_getenv(sh->env, to_search, ft_strlen(to_search))) != NULL)
						{
							free(to_search);
							to_search = ft_strdup(substitute + 1);
							return (to_search);
						}
						substitute = ft_strdup("\0");
					}
					free(to_search);
					return (substitute);
				}
				return (NULL);
			}
			*pos = *pos + 1;
		}
	}
	return (NULL);
}

char			*dollar_substitute(t_42sh *sh, char *str, int *pos)
{
	char		*new;

	new = NULL;
	if (str[*pos + 1] == '{')
	{
		*pos = *pos + 2;
		new = substitute_param(sh, str, pos);
	}/*if (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str + 1] 
	== '(' && sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str + 2] == '(')*/
	//	substitute_arithmetic(sh);
	return (new);
}

char			*check_substitute(t_42sh *sh, char *str, int *error)
{
	int			i;
	char		*substitute;
	char		*new;
	char		*tmp;
	char		*tmp2;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (i > 0)
				tmp = ft_strsub(str, 0 , i);
			else
				tmp = ft_strdup("\0");
			substitute = dollar_substitute(sh, str, &i);
			if (substitute == NULL)
			{
				ft_putendl_fd("42sh : bad substitution", 2);
				free(tmp);
				*error = 1;
				return (NULL);
			}
			tmp2 = ft_strjoin(tmp, substitute);
			new = ft_strjoin(tmp2, str + i + 1);
			free(tmp);
			free(tmp2);
			free(substitute);
		}
		i++;
	}
	return (new);
}

int			check_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_var	*new_var(char **line)
{
	t_var *new;

	if (!(new = malloc(sizeof(t_var))))
		print_error(_ENOMEM, 1);
	new->to_sub = ft_strdup(line[0]);
	new->sub = ft_strdup(line[1]);
	new->next = NULL;
	return (new);
}

int			check_var(t_var_mark **var, char **split)
{
	int i;
	t_var *start;

	i = 0;
	start = (*var)->begin;
	if ((*var)->size == 0)
		return (-1);
	while (i < (*var)->size)
	{
		if (ft_strequ(start->to_sub, split[0]) == 1)
		{
			ft_strdel(&start->sub);
			start->sub = ft_strdup(split[1]);
			return (0);
		}
		start = start->next;
		i++;
	}
	return (-1);
}

int		check_valid_var(char *str)
{
	int		i;

	i = 0;
	if (ft_isalpha(str[i]) != 1)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

void	add_to_varlist(t_42sh *sh, char **split)
{
	t_var *new;

	if (check_valid_var(split[0]) == 0)
	{
		ft_putendl_fd("variable can contain only alphanumeric caracters.", 2);
		return ;
	}
	if (check_var(&sh->var, split) == 0)
		return ;
	new = new_var(split);
	if (sh->var->size == 0)
		sh->var->begin = new;
	else
	{
		new->next = sh->var->begin;
		sh->var->begin = new;
	}
	sh->var->size++;
}

int				check_env(t_env **env, char **split)
{
	t_env		*tmp;
	int			len;
	char		*new;

	len = ft_strlen(split[0]);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(split[0], tmp->str, len))
		{
			free(tmp->str);
			new = ft_strjoin(split[0], "=");
			tmp->str = ft_strjoin(new, split[1]);
			free(new);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			check_local_variable(t_42sh *sh, char *str)
{
	char **split;

	if (check_equal(str) != 1)
		return ;
	split = ft_strsplit(str, '=');
	if (check_env(&sh->env, split) == 1)
	{
		if (ft_strequ(split[0],"PATH") == 1)
			reset_hashtable(&sh->hashtable);
		free(split[0]);
		free(split[1]);
		free(split);
		return ;
	}
	add_to_varlist(sh, split);
	free(split[0]);
	free(split[1]);
	free(split);
}

int				parse_test(t_42sh *sh)
{
	int			i;
	char		*tmp;
	int			error;

	i = 0;
	error = 0;
	while (sh->argv->argv[i])
	{
		if ((tmp = check_substitute(sh, sh->argv->argv[i], &error)) != NULL)
		{
			free(sh->argv->argv[i]);
			sh->argv->argv[i] = ft_strdup(tmp);
			free(tmp);
		}
		else if (tmp == NULL && error == 1)
			return (0);
		check_local_variable(sh, sh->argv->argv[i]);
		i++;
	}
	return (1);
}
