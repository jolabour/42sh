/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 07:38:19 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 20:52:40 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H

# define AST_H

# include "sh.h"

typedef struct s_42sh		t_42sh;

/*
**							struct
*/

typedef struct				s_node
{
	t_tok					token;
	char					*data;
	struct s_node			*left;
	struct s_node			*right;
	struct s_node			*parent;
	struct s_node			*redir;
}							t_node;

typedef struct				s_ast
{
	t_node					*begin;
	t_node					*current;
	t_node					*list;
}							t_ast;

/*
**							globals
*/

extern int					(*g_asttab[])(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);

/*
**							ft_ast.c
*/

void						ft_error_unexpected(t_node *list);
int							ft_build_ast(t_ast *ast, t_42sh *shell);

/*
**							ft_ast_command.c
*/

int							ft_ast_command(t_node **begin, t_node **current);
int							ft_ast_word(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);

/*
**							ft_ast_compound.c
*/

int							ft_ast_lpar(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_rpar(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_lbrace(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_rbrace(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);

/*
**							ft_ast_free.c
*/

void						ft_ast_freeone(t_node **list);
void						ft_ast_free(t_node *ast);

/*
**							ft_ast_is.c
*/

int							ft_ast_isassignment(t_node *current, t_node *list);
int							ft_ast_iscommand(t_node *current);
int							ft_ast_isseparator(t_node *current);
int							ft_ast_isbreakline(t_node *current);
int							ft_ast_isincompound(t_node *current);

/*
**							ft_ast_push_one_back.c
*/

void						ft_ast_push_one_back_left(t_node **from,
		t_node *to);
void						ft_ast_push_one_back_right(t_node **from,
		t_node *to);
void						ft_ast_push_one_back_redir(t_node **from,
		t_node *to);

/*
**							ft_ast_redir.c
*/

int							ft_ast_io_number(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_redir(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_readheredoc(t_node *heredoc, char *delim,
		t_42sh *shell);
int							ft_ast_heredoc(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_closefd(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);

/*
**							ft_ast_separators.c
*/

int							ft_ast_newline(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_pipe(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_separator(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);
int							ft_ast_and_or(t_node **begin, t_node **current,
		t_node **list, t_42sh *shell);

/*
**							ft_ast_tools.c
*/

t_node						*ft_new_node(void);
t_node						*ft_toklist_to_node(t_lex *lex);
void						ft_ast_insert_parent(t_node **begin,
		t_node **current, t_node **list);
int							ft_ast_continue_list(t_node **list, t_42sh *shell);

#endif
