/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 01:51:22 by geargenc          #+#    #+#             */
/*   Updated: 2019/03/20 02:33:57 by geargenc         ###   ########.fr       */
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
	{"|", PIPE},
	{"&", AND},
	{";", SEMI},
	{"<", LESS},
	{">", GREAT},
	{"(", LPAR},
	{")", RPAR},
	{"{", LBRACE},
	{"}", RBRACE},
	{"&&", AND_IF},
	{"||", OR_IF},
	{"<<", DLESS},
	{">>", DGREAT},
	{"<&", LESSAND},
	{"<&-", LESSANDDASH},
	{">&", GREATAND},
	{">&-", GREATANDDASH},
	{"<>", LESSGREAT},
	{"<<-", DLESSDASH},
	{">|", CLOBBER},
	{NULL, NONE}
};

t_tokcond				g_tokcond[] =
{
	{&ft_lex_operator, 0, 0},
	{&ft_lex_notoperator, 0, 0},
	{&ft_lex_newline, 0, 0},
	{&ft_lex_backslash, 1, 1},
	{&ft_lex_quote, 0, 0},
	{&ft_lex_dquote, 0, 0},
	{&ft_lex_dollar, 1, 1},
	{&ft_lex_bquote, 1, 1},
	{&ft_lex_ionumber, 0, 0},
	{&ft_lex_newoperator, 0, 0},
	{&ft_lex_blank, 0, 0},
	{&ft_lex_sharp, 0, 1},
	{&ft_lex_word, 1, 1},
	{&ft_lex_newword, 0, 0}
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
	{"fc", &builtin_fc},
	{"set", &builtin_set},
	{"unset", &builtin_unset},
	{"export", &builtin_export},
	{NULL, NULL}
};

#endif
