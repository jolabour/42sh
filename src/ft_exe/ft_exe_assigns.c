/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_assigns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:33:39 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 09:35:44 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			ft_add_tmp_env(char *var, char *value, t_42sh *shell)
{
	char		**newenv;
	int			i;

	i = 0;
	if (ft_strequ(var, "PATH=") == 1)
		reset_hashtable(&shell->hashtable);
	while (shell->copy_env[i] && !ft_strnequ(var, shell->copy_env[i],
		ft_strlen(var)))
		i++;
	if (shell->copy_env[i])
	{
		free(shell->copy_env[i]);
		shell->copy_env[i] = ft_strjoin(var, value);
	}
	else
	{
		newenv = (char **)ft_malloc_exit((i + 2) * sizeof(char *));
		i = -1;
		while (shell->copy_env[++i])
			newenv[i] = shell->copy_env[i];
		newenv[i] = ft_strjoin(var, value);
		newenv[i + 1] = NULL;
		free(shell->copy_env);
		shell->copy_env = newenv;
	}
}

int				ft_tmp_assigns(t_node *current, t_42sh *shell)
{
	char		*var;
	char		*value;

	current = current->left;
	while (current)
	{
		var = ft_strchr(current->data, '=');
		if (!(value = ft_simple_expanse(var + 1, shell)))
			return (-1);
		var = ft_strsub(current->data, 0, var - current->data + 1);
		ft_add_tmp_env(var, value, shell);
		free(var);
		free(value);
		current = current->left;
	}
	return (0);
}

int				ft_sustained_assigns(t_node *current, t_42sh *shell)
{
	char		*var;
	char		*value;

	current = current->left;
	while (current)
	{
		var = ft_strchr(current->data, '=');
		if (!(value = ft_simple_expanse(var + 1, shell)))
			return (-1);
		var = ft_strsub(current->data, 0, var - current->data + 1);
		var = ft_strjoinfree(var, value, 3);
		check_local_variable(shell, var);
		free(var);
		current = current->left;
	}
	return (0);
}

int				ft_assigns(t_node *current, t_42sh *shell)
{
	free_tab(shell->copy_env);
	shell->copy_env = list_to_tab(shell->env, shell->copy_env);
	if (current->left)
	{
		if (!shell->argv->argv[0])
			return (ft_sustained_assigns(current, shell));
		else
			return (ft_tmp_assigns(current, shell));
	}
	return (0);
}
