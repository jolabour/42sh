/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:21:23 by jolabour          #+#    #+#             */
/*   Updated: 2019/04/12 12:24:17 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "ft_global.h"

void		ft_init(t_42sh *shell)
{
	shell->pid = getpid();
	shell->pgid = getpgrp();
	shell->foreground = 0;
	signal(SIGINT, &ft_handler);
	if (isatty(STDIN_FILENO))
	{
		while (tcgetpgrp(STDIN_FILENO) != shell->pgid)
			kill(-shell->pgid, SIGTTIN);
		shell->pgid = 0;
		ft_init_signals();
		setpgid(shell->pid, shell->pid);
		tcsetpgrp(STDIN_FILENO, shell->pid);
		tcgetattr(STDIN_FILENO, &(shell->term));
		shell->foreground = 1;
	}
	shell->forked = 0;
	shell->jobs = NULL;
	shell->current = NULL;
	shell->retval = 0;
	shell->tmp_fds = NULL;
	shell->last_bg = 0;
	shell->exit_lock = 0;
	shell->buffer_mode = false;
}

int			main(int argc, char **argv, char **env)
{
	t_42sh	sh;

	(void)argc;
	sh.args = argv;
	init_shell(&sh, env);
	ft_init(&sh);
	if (!(env[0]))
		exit(0);
	while (42)
	{
		sh.need_get_line = true;
		process(&sh);
		ft_strdel(&sh.stdin->input);
		free(sh.stdin);
		del_history(sh.history_mark);
	}
	free(sh.argv);
	return (0);
}
