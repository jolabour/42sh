/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_continue_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:42:32 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 06:45:13 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_continue_line_buffer(t_42sh *shell, char **line)
{
	char	*tmp;

	tmp = shell->buffer ? ft_strchr(shell->buffer, '\n') : NULL;
	*line = tmp ? ft_strsub(shell->buffer, 0, tmp - shell->buffer + 1)
		: shell->buffer;
	if (tmp)
	{
		tmp = ft_strdup(tmp + 1);
		free(shell->buffer);
		shell->buffer = tmp;
	}
	else
		shell->buffer = NULL;
	return (*line ? 1 : 0);
}

int			ft_continue_line_stdin(t_42sh *shell, char **line)
{
	int		ret;

	if (!shell->pgid)
	{
		shell->prompt = "> ";
		prompt(shell->env, shell);
	}
	else
		shell->prompt_len = 0;
	free(shell->stdin->input);
	free(shell->stdin);
	del_history(shell->history_mark);
	ret = get_line(shell);
	*line = ret == 1 ? ft_strdup(shell->stdin->input) : NULL;
	return (ret);
}

int			ft_continue_line(t_42sh *shell, char **line, char *matching)
{
	int		ret;

	if (shell->buffer_mode)
		ret = ft_continue_line_buffer(shell, line);
	else
		ret = ft_continue_line_stdin(shell, line);
	if (*line == NULL && ret == 0)
	{
		if (matching && *matching)
		{
			ft_putstr_fd("42sh: unexpected EOF while looking for matching `",
				STDERR_FILENO);
			ft_putstr_fd(matching, STDERR_FILENO);
			ft_putstr_fd("\'\n", STDERR_FILENO);
		}
		else if (matching)
			ft_putstr_fd("42sh: syntax error: unexpected end of file\n",
				STDERR_FILENO);
	}
	return (ret);
}
