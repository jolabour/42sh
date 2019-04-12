/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 01:51:22 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 18:59:43 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOBAL_H

# define FT_GLOBAL_H

# include "sh.h"

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
	{&ft_lex_newline, false},
	{&ft_lex_backslash, true},
	{&ft_lex_quote, false},
	{&ft_lex_dquote, false},
	{&ft_lex_dollar, true},
	{&ft_lex_bquote, true},
	{&ft_lex_ionumber, false},
	{&ft_lex_operator, false},
	{&ft_lex_blank, false},
	{&ft_lex_sharp, false},
	{&ft_lex_word, true},
};

int						(*g_asttab[])(t_node **begin, t_node **current,
						t_node **list, t_42sh *shell) =
{
	NULL,
	&ft_ast_word,
	NULL,
	NULL,
	&ft_ast_newline,
	&ft_ast_io_number,
	NULL,
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
	NULL
};

int						(*g_exetab[])(t_node *current, t_42sh *shell) =
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	ft_exe_pipe,
	ft_exe_and,
	ft_exe_semi,
	ft_exe_great,
	ft_exe_less,
	NULL,
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
	NULL,
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
	{"cd", &builtin_cd},
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
						t_txtlist **current, bool *dquote) =
{
	&ft_parse_tilde,
	&ft_parse_var,
	&ft_parse_bquote,
	&ft_parse_backslash,
	&ft_parse_quote,
	&ft_parse_text
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
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&ft_cmdline_sep,
	&ft_cmdline_sep,
	&ft_cmdline_sep,
	&ft_cmdline_redir,
	&ft_cmdline_redir,
	NULL,
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
	NULL,
	&ft_cmdline_brace,
	&ft_cmdline_command
};

int					g_intr;

t_class				g_classestab[] =
{
	{"[:alnum:]",
		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"},
	{"[:alpha:]", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"},
	{"[:blank:]", " \t"},
	{"[:cntrl:]", "\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xA\xB\xC\xD\xE\xF\x10\x11"
		"\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x7F"},
	{"[:digit:]", "0123456789"},
	{"[:graph:]", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"},
	{"[:lower:]", "abcdefghijklmnopqrstuvwxyz"},
	{"[:print:]", " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"},
	{"[:punct:]", "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"},
	{"[:space:]", " \t\n\r\v\f"},
	{"[:upper:]", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
	{"[:xdigit:]", "0123456789ABCDEFabcdef"},
	{NULL, NULL}
};

t_getmatch			g_getmatchtab[] =
{
	&ft_getmatch_wcard,
	&ft_getmatch_qmark,
	&ft_getmatch_hook,
	&ft_getmatch_text
};

t_match				g_matchtab[] =
{
	&ft_match_end,
	&ft_match_text,
	&ft_match_wcard,
	&ft_match_qmark,
	&ft_match_hook,
	&ft_match_rhook
};

t_expparamfunc	g_expparamtab[] =
{
	{":-", &ft_expparam_cnminus},
	{"-", &ft_expparam_minus},
	{":=", &ft_expparam_cnequal},
	{"=", &ft_expparam_equal},
	{":?", &ft_expparam_cnqmark},
	{"?", &ft_expparam_qmark},
	{":+", &ft_expparam_cnplus},
	{"+", &ft_expparam_plus},
	{"%", &ft_expparam_pcent},
	{"%%", &ft_expparam_dpcent},
	{"#", &ft_expparam_sharp},
	{"##", &ft_expparam_dsharp},
	{"", &ft_expparam_nofunc},
	{NULL, NULL}
};

#endif
