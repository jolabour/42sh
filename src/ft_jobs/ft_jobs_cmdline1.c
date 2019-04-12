/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_cmdline1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:17:57 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:19:43 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*ft_cmdline_sep(t_node *command)
{
	char		*line;

	line = g_cmdlinetab[command->left->token](command->left);
	line = ft_strjoinfree(line, " ", 1);
	line = ft_strjoinfree(line, command->data, 1);
	if (command->right)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->right->token](command->right), 3);
	}
	return (line);
}

char			*ft_cmdline_redir(t_node *command)
{
	char		*line;

	line = ft_strdup(command->left ? command->left->data : "");
	line = ft_strjoinfree(line, command->data, 1);
	line = ft_strjoinfree(line, " ", 1);
	line = ft_strjoinfree(line, command->right->data, 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}

char			*ft_cmdline_par(t_node *command)
{
	char		*line;

	line = ft_strdup("( ");
	line = ft_strjoinfree(line,
		g_cmdlinetab[command->right->token](command->right), 3);
	line = ft_strjoinfree(line, " )", 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}

char			*ft_cmdline_redir_and(t_node *command)
{
	char		*line;

	line = ft_strdup(command->left ? command->left->data : "");
	line = ft_strjoinfree(line, command->data, 1);
	line = ft_strjoinfree(line, command->right->data, 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}

char			*ft_cmdline_redir_close(t_node *command)
{
	char		*line;

	line = ft_strdup(command->left ? command->left->data : "");
	line = ft_strjoinfree(line, command->data, 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}
