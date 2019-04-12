/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 07:17:54 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 08:50:23 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "sh.h"

typedef struct s_42sh		t_42sh;

/*
**							enum
*/

typedef enum				e_tok
{
	NONE = 0,
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,
	OPP,
	PIPE,
	AND,
	SEMI,
	GREAT,
	LESS,
	LPAR,
	RPAR,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESSAND,
	LESSANDDASH,
	GREATAND,
	GREATANDDASH,
	LESSGREAT,
	DLESSDASH,
	CLOBBER,
	LBRACE,
	RBRACE,
	COMMAND
}							t_tok;

/*
**							struct
*/

typedef struct				s_toktab
{
	char					*str;
	t_tok					token;
	bool					alias_recognition;
	bool					redir_op;
}							t_toktab;

typedef struct				s_toklist
{
	t_tok					token;
	size_t					start;
	size_t					len;
	struct s_toklist		*next;
}							t_toklist;

typedef struct				s_lex
{
	char					*input;
	size_t					index;
	t_toklist				*begin;
	t_toklist				*current;
	bool					alias_recognition;
	bool					redir_op;
	size_t					ignore_alias;
}							t_lex;

typedef struct				s_tokcond
{
	int						(*cond)(t_lex *, t_42sh *);
	int						dquote_mode;
	int						sub_mode;
}							t_tokcond;

/*
**							globals
*/

extern char					*g_tokstr[];
extern t_toktab				g_toktab[];
extern t_tokcond			g_tokcond[];

/*
**							ft_lexer.c
*/

int							ft_lexer(t_lex *lex, t_42sh *shell);

/*
**							ft_lex_bquote.c
*/

int							ft_lex_bquote_mode(t_lex *lex, t_42sh *shell);
int							ft_lex_bquote(t_lex *lex, t_42sh *shell);

/*
**							ft_lex_delimiter.c
*/

void						ft_free_last_toklist(t_lex *lex);
void						ft_lex_replace_alias(t_lex *lex, char *alias);
void						ft_lex_assignment(t_lex *lex);
int							ft_lex_delimiter(t_lex *lex, t_42sh *shell);

/*
**							ft_lex_dollar.c
*/

int							ft_lex_sub_mode(t_lex *lex, t_42sh *shell);
int							ft_lex_dollar_brace(t_lex *lex, t_42sh *shell);
int							ft_lex_dollar_par(t_lex *lex, t_42sh *shell);
int							ft_lex_dollar(t_lex *lex, t_42sh *shell);

/*
**							ft_lex_operator.c
*/

int							ft_find_operator(t_lex *lex);
int							ft_lex_operator(t_lex *lex, t_42sh *shell);

/*
**							ft_lex_other_rules.c
*/

int							ft_lex_newline(t_lex *lex, t_42sh *shell);
int							ft_lex_ionumber(t_lex *lex, t_42sh *shell);
int							ft_lex_blank(t_lex *lex, t_42sh *shell);
int							ft_lex_sharp(t_lex *lex, t_42sh *shell);
int							ft_lex_word(t_lex *lex, t_42sh *shell);

/*
**							ft_lex_quoting.c
*/

int							ft_lex_backslash(t_lex *lex, t_42sh *shell);
int							ft_lex_quote(t_lex *lex, t_42sh *shell);
int							ft_lex_dquote_mode(t_lex *lex, t_42sh *shell);
int							ft_lex_dquote(t_lex *lex, t_42sh *shell);

/*
**							ft_lex_tools.c
*/

t_toklist					*ft_newtoklist(void);
void						ft_add_toklist(t_lex *lex, t_tok token);
int							ft_lex_continue_line(t_lex *lex, t_42sh *shell,
		char *matching);
void						ft_lex_free(t_lex *lex);

#endif
