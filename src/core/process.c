/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:47:49 by jolabour          #+#    #+#             */
/*   Updated: 2019/01/10 20:35:26 by ttresori         ###   ########.fr       */
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
		if ((status = execve(sh->valide_path, sh->tokens, sh->copy_env)) == -1)
			ft_putendl_fd(sh->tokens[0], 2);
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

void			check_builtin(t_42sh *sh)
{
	if (ft_strequ(sh->argv->argv[0], "test") == 1)
	{
		builtin_test(sh);
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

void			substitute_error(t_42sh *sh)
{
	

void			check_substitute(t_42sh *sh)
{
  sh->argv->cur_str = 0;
  while (sh->argv->argv[sh->argv->cur_str] != NULL)
    {
      sh->argv->pos_str = 0;
      while(sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str])
	{
	  if (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str] == '$' && sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str + 1] == '?')
	 {   if (substitute_error(sh) == 0)
			return ;
	  }
	  else
	    sh->argv->pos_str++;
	}
	sh->argv->cur_str++;
    }
}

void			process(t_42sh *sh)
{
	BUCKET_CONTENT	*bucket_entry;
	//int j;

	prompt(sh->env, sh);	

	if (get_line(sh) != 1)
		return ;
if (sh->stdin->len_line == 0 || !sh->stdin->input)
	return ;
	ft_lexer(sh);
	add_history(sh, sh->stdin->input, sh->path_history);
	if (ft_strcmp(sh->stdin->input, "exit\n") == 0)
	reset_term(sh);
	sh->argv = malloc(sizeof(t_argv));
	sh->argv->argv = ft_strsplitset(sh->stdin->input, " \t\n");
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
	}
}
