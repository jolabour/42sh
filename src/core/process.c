/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 07:47:49 by jolabour          #+#    #+#             */
/*   Updated: 2018/12/17 03:48:44 by jolabour         ###   ########.fr       */
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
	if (access(sh->tokens[0], F_OK) == 0)
	{
		if (!(tmp2 = ft_strdup(sh->tokens[0])))
			print_error(_ENOMEM, 1);
		return (tmp2);
	}
	if (sh->bin_dirs)
	{
		while (sh->bin_dirs[i])
		{
			if (!(tmp = ft_strjoin(sh->bin_dirs[i], "/")))
				print_error(_ENOMEM, 1);
			if (!(tmp2 = ft_strjoin(tmp, sh->tokens[0])))
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

void			process(t_42sh *sh)
{
	//BUCKET_CONTENT	*bucket_entry;

	prompt(sh->env, sh);
	if (get_line(sh) != 1)
		return ;
	if (sh->stdin->len_line == 0 || !sh->stdin->input)
		return ;
	ft_lexer(sh);
	add_history(sh, sh->stdin->input, sh->path_history);
	//parser(sh);
	/*sh->tokens = ft_strsplitset(sh->input, " \t");
	if ((bucket_entry = ht_lookup(sh->tokens[0], &sh->hashtable)) != NULL)
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
	ft_putnbr(sh->size_of_window);
	ft_putnbr(sh->line_pos + sh->prompt_len);
	ft_putnbr(sh->len_line);*/
}
