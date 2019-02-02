/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:47:49 by jolabour          #+#    #+#             */
/*   Updated: 2019/01/25 02:40:03 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sh.h"

void	get_fork(t_42sh *sh)
{
	pid_t	father;
	int		status;

	father = fork();
	if (father > 0)
		wait(0);
	if (father == 0)
	{
		if ((status = execve(sh->valide_path, sh->argv->argv, sh->copy_env)) == -1)
			ft_putendl_fd("sh->tokens[0]", 2);
		exit(status);
	}
}

char	*check_access(t_42sh *sh)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (access(sh->argv->argv[0], F_OK) == 0)
	{
		if (!(tmp2 = ft_strdup(sh->argv->argv[0])))
			print_error(_ENOMEM, 1);
		return (tmp2);
	}
	if (sh->bin_dirs)
	{
		while (sh->bin_dirs[i])
		{
			if (!(tmp = ft_strjoin(sh->bin_dirs[i], "/")))
				print_error(_ENOMEM, 1);
			if (!(tmp2 = ft_strjoin(tmp, sh->argv->argv[0])))
				print_error(_ENOMEM, 1);
			ft_strdel(&tmp);
			if (access(tmp2, F_OK) == 0)
				return (tmp2);
			ft_strdel(&tmp2);
			i++;
		}
	}
	return (NULL);
}

int			check_builtin(t_42sh *sh)
{
	if (ft_strequ(sh->argv->argv[0], "test") == 1)
	{
		builtin_test(sh);
		return (1);
	}
	if (ft_strequ(sh->argv->argv[0], "echo") == 1)
	{
		builtin_echo(sh);
		return (1);
	}
	if (ft_strequ(sh->argv->argv[0], "alias") == 1)
	{
		builtin_alias(sh);
		return (1);
	}
	return (0);
}

int				ft_len_argv(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void			process(t_42sh *sh)
{
	BUCKET_CONTENT	*bucket_entry;

	prompt(sh->env, sh);

	//if (sh->need_get_line == true)
	if (get_line(sh) != 1)
			return ;
	if (sh->stdin->len_line == 0 || !sh->stdin->input)
		return ;
	ft_lexer(sh);
	if (ft_strcmp(sh->stdin->input, "exit\n") == 0)
		reset_term(sh);
	check_substitute_history(sh);
	if (sh->history_mark->error_code == 0)
		add_history(sh, sh->stdin->input, sh->path_history);
	sh->argv->argv = ft_strsplitset(sh->stdin->input, " \t\n");
	if (!sh->argv->argv[0])
		return ;
	sh->argv->size = ft_len_argv(sh->argv->argv);
	check_substitute(sh);
	if (check_builtin(sh) != 1)
	{
		if ((bucket_entry = ht_lookup(sh->argv->argv[0], &sh->hashtable)) != NULL)
			sh->valide_path = ft_strdup(bucket_entry->path);
		else
		{
			sh->valide_path = check_access(sh);
			ft_putendl("donne un binaire gorille");
			return ;
		}
		if (access(sh->valide_path, X_OK) == -1)
		{
			ft_putendl("t'as pas les droits victimes");
			ft_strdel(&sh->valide_path);
			return ;
		}
		get_fork(sh);
		ft_strdel(&sh->valide_path);
	}
}
