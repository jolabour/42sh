/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:25:58 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 05:48:40 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
**				lexer
*/

void			ft_print_toklist(char *input, t_toklist *list)
{
	while (list)
	{
		ft_putendl(g_tokstr[list->token]);
		ft_putnbr(list->start);
		ft_putchar('\n');
		ft_putnbr(list->len);
		ft_putchar('\n');
		write(1, input + list->start, list->len);
		ft_putchar('\n');
		ft_putstr("----------------------------------------\n");
		list = list->next;
	}
}

/*
**				ast
*/

void			ft_line_spaces(int rec)
{
	while (rec > 0)
	{
		write(1, "    |", 5);
		rec--;
	}
}

#include <stdarg.h>

void			ft_printer(char *format, ...)
{
	va_list		ap;
	char		*res;
	int			i;

	va_start(ap, format);
	vasprintf(&res, format, ap);
	va_end(ap);
	i = 0;
	while (res[i])
	{
		if (res[i] == '\n')
			write(1, "\\n", 2);
		else
			write(1, res + i, 1);
		i++;
	}
	write(1, "\n", 1);
	free(res);
}

void			ft_print_ast(t_node *ast, int rec)
{
	ft_line_spaces(rec);
	ft_printer("    +token [%s]", g_tokstr[ast->token]);
	ft_line_spaces(rec);
	ft_printer("    +data [%s]", ast->data);
	if (ast->left)
	{
		ft_line_spaces(rec);
		ft_printer("    +left :");
		ft_print_ast(ast->left, rec + 1);
	}
	if (ast->right)
	{
		ft_line_spaces(rec);
		ft_printer("    +right :");
		ft_print_ast(ast->right, rec + 1);
	}
	if (ast->redir)
	{
		ft_line_spaces(rec);
		ft_printer("    +redirs :");
		ft_print_ast(ast->redir, rec + 1);
	}
}

/*
**				expansions
*/

void			ft_print_txtlist(char *input, t_txtlist *list)
{
	while (list)
	{
		ft_putstr("[");
		ft_putstr(g_txtstr[list->token]);
		ft_putchar('-');
		ft_putnbr(list->start);
		ft_putchar('-');
		ft_putnbr(list->len);
		ft_putchar('-');
		if (list->dquote)
			ft_putchar('\"');
		write(1, input + list->start, list->len);
		if (list->dquote)
			ft_putchar('\"');
		ft_putchar(']');
		list = list->next;
	}
	ft_putchar('\n');
}

void			ft_getmatch_print(t_matchlist *list)
{
	int			i;

	while (list)
	{
		ft_putstr("[");
		ft_putstr(g_matchstr[list->token]);
		if (list->token == MATCH_HOOK || list->token == MATCH_RHOOK)
		{
			ft_putstr("|");
			i = 0;
			while (i < 128)
			{
				if (list->hparam[i])
				{
					if (i >= ' ' && i <= '~')
						ft_putchar((char)i);
					else
					{
						ft_putstr("[");
						ft_putnbr(i);
						ft_putstr("]");
					}
				}
				i++;
			}
		}
		else if (list->token == MATCH_TEXT)
		{
			ft_putstr("|");
			if (list->tparam >= ' ' && list->tparam <= '~')
				ft_putchar(list->tparam);
			else
			{
				ft_putstr("[");
				ft_putnbr(list->tparam);
				ft_putstr("]");
			}
		}
		ft_putstr("]");
		list = list->next;
	}
	ft_putstr("\n");
}

/*
**				exe and job_control
*/

void			ft_write_status(int status)
{
	ft_putstr("WIFEXITED: ");
	ft_putnbr(WIFEXITED(status));
	ft_putstr(" - WEXITSTATUS: ");
	ft_putnbr(WEXITSTATUS(status));
	ft_putstr("\nWIFSIGNALED: ");
	ft_putnbr(WIFSIGNALED(status));
	ft_putstr(" - WTERMSIG: ");
	ft_putnbr(WTERMSIG(status));
	ft_putstr("\nWIFSTOPPED: ");
	ft_putnbr(WIFSTOPPED(status));
	ft_putstr(" - WSTOPSIG: ");
	ft_putnbr(WSTOPSIG(status));
	ft_putstr("\nWIFCONTINUED: ");
	ft_putnbr(WIFCONTINUED(status));
	ft_putstr("\nWCOREDUMP: ");
	ft_putnbr(WCOREDUMP(status));
	ft_putstr("\nisatty: ");
	ft_putnbr(isatty(1));
	ft_putstr("\n");
}

