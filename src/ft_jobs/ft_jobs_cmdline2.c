/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_cmdline2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 11:20:28 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 11:35:28 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*ft_cmdline_brace(t_node *command)
{
	char		*line;

	line = ft_strdup("{ ");
	line = ft_strjoinfree(line,
		g_cmdlinetab[command->right->token](command->right), 3);
	line = ft_strjoinfree(line, " }", 1);
	if (command->redir)
	{
		line = ft_strjoinfree(line, " ", 1);
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	}
	return (line);
}

char			*ft_cmdline_assigns(t_node *command)
{
	char		*line;
	t_node		*node;

	line = ft_strdup("");
	node = command->left;
	while (node)
	{
		line = ft_strjoinfree(line, node->data, 1);
		if (node->left || command->right || command->redir)
			line = ft_strjoinfree(line, " ", 1);
		node = node->left;
	}
	return (line);
}

char			*ft_cmdline_words(t_node *command)
{
	char		*line;
	t_node		*node;

	line = ft_strdup("");
	node = command->right;
	while (node)
	{
		line = ft_strjoinfree(line, node->data, 1);
		if (node->right || command->redir)
			line = ft_strjoinfree(line, " ", 1);
		node = node->right;
	}
	return (line);
}

char			*ft_cmdline_command(t_node *command)
{
	char		*line;

	line = ft_strdup("");
	if (command->left)
		line = ft_strjoinfree(line, ft_cmdline_assigns(command), 3);
	if (command->right)
		line = ft_strjoinfree(line, ft_cmdline_words(command), 3);
	if (command->redir)
		line = ft_strjoinfree(line,
			g_cmdlinetab[command->redir->token](command->redir), 3);
	return (line);
}
