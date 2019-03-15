/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:47:49 by jolabour          #+#    #+#             */
/*   Updated: 2019/03/15 02:01:37 by geargenc         ###   ########.fr       */
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

char	*check_access(t_42sh *sh, int pos)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (access(sh->argv->argv[pos], F_OK) == 0)
	{
		if (!(tmp2 = ft_strdup(sh->argv->argv[pos])))
			print_error(_ENOMEM, 1);
		return (tmp2);
	}
	if (sh->bin_dirs)
	{
		while (sh->bin_dirs[i])
		{
			if (!(tmp = ft_strjoin(sh->bin_dirs[i], "/")))
				print_error(_ENOMEM, 1);
			if (!(tmp2 = ft_strjoin(tmp, sh->argv->argv[pos])))
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
	if (ft_strequ(sh->argv->argv[0], "unalias") == 1)
	{
		builtin_unalias(sh);
		return (1);
	}
	if (ft_strequ(sh->argv->argv[0], "hash") == 1)
	{
		builtin_hash(sh);
		return (1);
	}
	if (ft_strequ(sh->argv->argv[0], "type") == 1)
	{
		builtin_type(sh);
		return (1);
	}
	if (ft_strequ(sh->argv->argv[0], "fc") == 1)
	{
		builtin_fc(sh);
		return (1);
	}
	if (ft_strequ(sh->argv->argv[0], "set") == 1)
	{
		builtin_set(sh);
		return (1);
	}
	if (ft_strequ(sh->argv->argv[0], "unset") == 1)
	{
		builtin_unset(sh);
		return (1);
	}
	if (ft_strequ(sh->argv->argv[0], "export") == 1)
	{
		builtin_export(sh);
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

void			substitute_alias(t_42sh *sh)
{
	int			i;
	t_alias		*tmp;

	i = 0;
	tmp = sh->alias->begin;
	while (i < sh->alias->size)
	{
		if (ft_strequ(tmp->to_sub, sh->argv->argv[0]) == 1)
		{
			ft_strdel(&sh->argv->argv[0]);
			sh->argv->argv[0] = ft_strdup(tmp->sub);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
}

void			free_tab(char **str)
{
	int			i;

	i = 0;
	while(str[i])
	{
		ft_strdel(&str[i]);
		i++;
	}
	free(str);
}

void			process(t_42sh *sh)
{
	// BUCKET_CONTENT	*bucket_entry;
	// char			*path;
	// int				i;
	void			*list;

	// i = 0;
	prompt(sh->env, sh);
	if (get_line(sh) != 1)
		return ;
	if (sh->stdin->len_line == 0 || !sh->stdin->input)
		return ;
	check_substitute_history(sh);
	if (sh->history_mark->error_code == 0 && ft_strcmp(sh->stdin->input, "fc\n") != 0)
		add_history(sh, sh->stdin->input, sh->path_history);
	if (!(list = ft_lexer(&(sh->stdin->input))))
		exit(2);
	if (!(list = ft_toklist_to_node((sh->stdin->input), list)))
		exit(2);
	// free((sh->stdin->input));
	if (!(list = ft_build_ast(list)))
		exit(2);
	g_exetab[((t_node *)list)->token](list, &(sh->shell));
	// ft_lexer(sh);
	// if (ft_strcmp(sh->stdin->input, "exit\n") == 0)
	// 	reset_term(sh);
	// sh->argv->argv = ft_strsplitset(sh->stdin->input, " \t\n");
	// if (!sh->argv->argv[0])
	// 	return ;
	// sh->argv->size = ft_len_argv(sh->argv->argv);
	//  if (parse_test(sh) == 0)
	// 	return ;
	// substitute_alias(sh);
	// free_tab(sh->copy_env);
	// sh->copy_env = list_to_tab(sh->env, sh->copy_env);
	// free_tab(sh->bin_dirs);
	// path = ft_getenv(sh->env, "PATH=", sizeof("PATH=") - 1);
	// if (path)
	// {
	// 	if ((sh->bin_dirs = ft_strsplit(path, ':')) == NULL)
	// 		print_error(_ENOMEM, 1);
	// }
	// if (check_builtin(sh) != 1)
	// {
	// 	if ((bucket_entry = ht_lookup(sh->argv->argv[0], &sh->hashtable)) != NULL)
	// 		sh->valide_path = ft_strdup(bucket_entry->path);
	// 	else
	// 	{
	// 		sh->valide_path = check_access(sh, 0);
	// 		if (sh->valide_path == NULL)
	// 		{
	// 			ft_putendl("donne un binaire gorille");
	// 			return ;
	// 		}
	// 		if (sh->argv->argv[0][0] != '/')
	// 			ht_insert(sh->valide_path, sh->argv->argv[0], &sh->hashtable);
	// 	}
	// 	if (access(sh->valide_path, X_OK) == -1)
	// 	{
	// 		ft_putendl("t'as pas les droits victimes");
	// 		ft_strdel(&sh->valide_path);
	// 		return ;
	// 	}
	// 	get_fork(sh);
	// 	ft_strdel(&sh->valide_path);
	// }
}
