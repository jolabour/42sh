/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 01:51:22 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/03 02:04:02 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOBAL_H

# define FT_GLOBAL_H

# include "sh.h"

char					*g_tokstr[] =
{
	"NONE",
	"WORD",
	"ASSIGNMENT_WORD",
	"NAME",
	"NEWLINE",
	"IO_NUMBER",
	"OPP",
	"PIPE",
	"AND",
	"SEMI",
	"GREAT",
	"LESS",
	"LPAR",
	"RPAR",
	"AND_IF",
	"OR_IF",
	"DLESS",
	"DGREAT",
	"LESSAND",
	"LESSANDDASH",
	"GREATAND",
	"GREATANDDASH",
	"LESSGREAT",
	"DLESSDASH",
	"CLOBBER",
	"LBRACE",
	"RBRACE",
	"COMMAND"
};

t_toktab				g_toktab[] =
{
	{"|", PIPE, 1, 0},
	{"&", AND, 1, 0},
	{";", SEMI, 1, 0},
	{"<", LESS, 0, 1},
	{">", GREAT, 0, 1},
	{"(", LPAR, 1, 0},
	{")", RPAR, 1, 0},
	{"{", LBRACE, 1, 0},
	{"}", RBRACE, 1, 0},
	{"&&", AND_IF, 1, 0},
	{"||", OR_IF, 1, 0},
	{"<<", DLESS, 0, 1},
	{">>", DGREAT, 0, 1},
	{"<&", LESSAND, 0, 1},
	{"<&-", LESSANDDASH, 0, 1},
	{">&", GREATAND, 0, 1},
	{">&-", GREATANDDASH, 0, 1},
	{"<>", LESSGREAT, 0, 1},
	{"<<-", DLESSDASH, 0, 1},
	{">|", CLOBBER, 0, 1},
	{NULL, NONE, 0, 0}
};

t_tokcond				g_tokcond[] =
{
	{&ft_lex_newline, 0, 0},
	{&ft_lex_backslash, 1, 1},
	{&ft_lex_quote, 0, 0},
	{&ft_lex_dquote, 0, 0},
	{&ft_lex_dollar, 1, 0},
	{&ft_lex_bquote, 1, 0},
	{&ft_lex_ionumber, 0, 0},
	{&ft_lex_operator, 0, 0},
	{&ft_lex_blank, 0, 0},
	{&ft_lex_sharp, 0, 0},
	{&ft_lex_word, 1, 1},
};

int						(*g_asttab[])(t_node **begin, t_node **current,
						t_node **list, t_42sh *shell) =
{
	&ft_ast_badtoken,
	&ft_ast_word,
	&ft_ast_badtoken,
	&ft_ast_badtoken,
	&ft_ast_newline,
	&ft_ast_io_number,
	&ft_ast_badtoken,
	&ft_ast_pipe,
	&ft_ast_separator,
	&ft_ast_separator,
	&ft_ast_redir,
	&ft_ast_redir,
	&ft_ast_lpar,
	&ft_ast_rpar,
	&ft_ast_and_or,
	&ft_ast_and_or,
	&ft_ast_heredoc,
	&ft_ast_redir,
	&ft_ast_redir,
	&ft_ast_closefd,
	&ft_ast_redir,
	&ft_ast_closefd,
	&ft_ast_redir,
	&ft_ast_heredoc,
	&ft_ast_redir,
	&ft_ast_lbrace,
	&ft_ast_rbrace,
	&ft_ast_badtoken
};

int						(*g_exetab[])(t_node *current, t_42sh *shell) =
{
	ft_exe_badtoken,
	ft_exe_badtoken,
	ft_exe_badtoken,
	ft_exe_badtoken,
	ft_exe_badtoken,
	ft_exe_badtoken,
	ft_exe_badtoken,
	ft_exe_pipe,
	ft_exe_and,
	ft_exe_semi,
	ft_exe_great,
	ft_exe_less,
	ft_exe_badtoken,
	ft_exe_rpar,
	ft_exe_and_if,
	ft_exe_or_if,
	ft_exe_dless,
	ft_exe_dgreat,
	ft_exe_lessand,
	ft_exe_lessanddash,
	ft_exe_greatand,
	ft_exe_greatanddash,
	ft_exe_lessgreat,
	ft_exe_dless,
	ft_exe_great,
	ft_exe_badtoken,
	ft_exe_rbrace,
	ft_exe_command
};

t_bttab					g_bttab[] =
{
	{"test", &builtin_test},
	{"echo", &builtin_echo},
	{"alias", &builtin_alias},
	{"unalias", &builtin_unalias},
	{"hash", &builtin_hash},
	{"type", &builtin_type},
	{"set", &builtin_set},
	{"unset", &builtin_unset},
	{"export", &builtin_export},
	{"jobs", &builtin_jobs},
	{"fg", &builtin_fg},
	{"bg", &builtin_bg},
	{"exit", &builtin_exit},
	{NULL, NULL}
};

t_spparam				g_spparamtab[] =
{
	{'$', &ft_spparam_dollar},
	{'?', &ft_spparam_qmark},
	{'!', &ft_spparam_bang},
	{'0', &ft_spparam_zero},
	{'\0', NULL}
};

int						(*g_txttab[])(char *word, size_t *index,
						t_txtlist **current, int *dquote) =
{
	&ft_parse_tilde,
	&ft_parse_var,
	&ft_parse_bquote,
	&ft_parse_backslash,
	&ft_parse_quote,
	&ft_parse_text
};

char					*g_txtstr[] =
{
	"TXT_NONE",
	"TEXT",
	"TILDE",
	"VAR",
	"BRACE_VAR",
	"CMD_SUB",
	"CMD_SUB_BQUOTE",
	"ARTH_EXPR"
};

int						(*g_exptab[])(t_txtlist *txt, t_42sh *shell) =
{
	NULL,
	&ft_exp_text,
	&ft_exp_tilde,
	&ft_exp_var,
	&ft_exp_brace,
	&ft_exp_sub,
	&ft_exp_bquote,
	&ft_exp_expr
};

char					*g_sigtab[] =
{
	"Unknown signal",
	"Hangup: 1",
	"Interrupt: 2",
	"Quit: 3",
	"Illegal instruction: 4",
	"Trace/BPT trap: 5",
	"Abort trap: 6",
	"EMT trap: 7",
	"Floating point exception: 8",
	"Killed: 9",
	"Bus error: 10",
	"Segmentation fault: 11",
	"Bad system call: 12",
	"Broken pipe: 13",
	"Alarm clock: 14",
	"Terminated: 15",
	"Urgent condition: 16",
	"Suspended (signal): 17",
	"Suspended: 18",
	"Continue: 19",
	"Child status: 20",
	"Stopped (tty input): 21",
	"Stopped (tty output): 22",
	"Possible I/O: 23",
	"Cputime limit exceeded: 24",
	"Filesize limit exceeded: 25",
	"Virtual timer expired: 26",
	"Profiling timer expired: 27",
	"Window resize: 28",
	"Status request: 29",
	"User defined signal 1: 30",
	"User defined signal 2: 31"
};

char			*g_sigabrevtab[] =
{
	"SIGUKWN",
	"SIGHUP",
	"SIGINT",
	"SIGQUIT",
	"SIGILL",
	"SIGTRAP",
	"SIGABRT",
	"SIGEMT",
	"SIGFPE",
	"SIGKILL",
	"SIGBUS",
	"SIGSEGV",
	"SIGSYS",
	"SIGPIPE",
	"SIGALRM",
	"SIGTERM",
	"SIGURG",
	"SIGSTOP",
	"SIGTSTP",
	"SIGCONT",
	"SIGCHLD",
	"SIGTTIN",
	"SIGTTOU",
	"SIGIO",
	"SIGXCPU",
	"SIGXFSZ",
	"SIGVTALRM",
	"SIGPROF",
	"SIGWINCH",
	"SIGINFO",
	"SIGUSR1",
	"SIGUSR2"
};

char				*(*g_cmdlinetab[])(t_node *command) =
{
	&ft_cmdline_badtoken,
	&ft_cmdline_badtoken,
	&ft_cmdline_badtoken,
	&ft_cmdline_badtoken,
	&ft_cmdline_badtoken,
	&ft_cmdline_badtoken,
	&ft_cmdline_badtoken,
	&ft_cmdline_sep,
	&ft_cmdline_sep,
	&ft_cmdline_sep,
	&ft_cmdline_redir,
	&ft_cmdline_redir,
	&ft_cmdline_badtoken,
	&ft_cmdline_par,
	&ft_cmdline_sep,
	&ft_cmdline_sep,
	&ft_cmdline_redir,
	&ft_cmdline_redir,
	&ft_cmdline_redir_and,
	&ft_cmdline_redir_close,
	&ft_cmdline_redir_and,
	&ft_cmdline_redir_close,
	&ft_cmdline_redir,
	&ft_cmdline_redir,
	&ft_cmdline_redir,
	&ft_cmdline_badtoken,
	&ft_cmdline_brace,
	&ft_cmdline_command
};

#endif
