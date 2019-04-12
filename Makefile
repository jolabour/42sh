# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jolabour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 09:19:56 by jolabour          #+#    #+#              #
#    Updated: 2019/04/12 11:36:26 by jolabour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 42sh

#
# Dirs
#

SRCS_DIR	= src
OBJS_DIR	= obj
LIB_DIR		= libft
INC_DIRS	= $(addsuffix includes, ./ $(LIB_DIR)/)
VPATH		= $(SRCS_DIR)

#
# Sources
#

SRCS		= core/main.c edit_line/list.c core/process.c utils/getenv.c \
			  core/init_shell.c edit_line/prompt.c \
			  edit_line/stdin.c edit_line/move_arrows.c edit_line/manip_input.c \
			  edit_line/insert_mode.c edit_line/move_word.c \
			  edit_line/control_action.c edit_line/keymap.c \
			  hashtable/hashtable.c edit_line/keymap_select.c \
			  hashtable/init_hashtable.c utils/ft_joinpath.c utils/env.c \
			  edit_line/select_mode.c edit_line/move_select_mode.c \
			  edit_line/action_select_mode.c edit_line/move_line.c edit_line/utils_stdin.c \
			  ft_lexer/ft_lex_bquote.c ft_lexer/ft_lex_delimiter.c \
			  ft_lexer/ft_lex_dollar.c ft_lexer/ft_lex_operator.c \
			  ft_lexer/ft_lex_other_rules.c ft_lexer/ft_lex_quoting.c \
			  ft_lexer/ft_lex_tools.c ft_lexer/ft_lexer.c \
			  ft_ast/ft_ast.c ft_ast/ft_ast_command.c \
			  ft_ast/ft_ast_compound.c ft_ast/ft_ast_free.c \
			  ft_ast/ft_ast_is.c ft_ast/ft_ast_push_one_back.c \
			  ft_ast/ft_ast_redir.c ft_ast/ft_ast_separators.c \
			  ft_ast/ft_ast_tools.c \
			  geff/main.c geff/ft_expanse.c \
			  histo/init_file_history.c histo/parser_history.c \
			  edit_line/move_histo.c histo/substitute_history.c \
			  builtin/test/test.c builtin/test/test_bcdef.c builtin/test/test_glprs.c \
			  builtin/test/test_suwxz.c builtin/test/test_l.c builtin/echo/echo.c  \
			  builtin/alias/alias.c  builtin/alias/list_alias.c \
			  builtin/test/exec_other.c builtin/test/test_other.c builtin/alias/unalias.c builtin/alias/error_alias.c \
			  builtin/hash/hash.c builtin/type/type.c builtin/type/print_type.c builtin/set/set.c builtin/unset/unset.c builtin/export/export.c armand/ft_check_exp_ari.c armand/ft_erase_space.c builtin/export/print_export.c \
			  armand/ft_logic_op.c armand/ft_true_op.c armand/ft_check_var.c armand/ft_itoa_exp_ari.c \
			  armand/ft_math_op.c armand/exp_ari.c builtin/unset/list_unset.c \
			  builtin/jobs/jobs.c builtin/exit/exit.c utils/ft_continue_line.c \
			  utils/tools.c utils/var.c utils/check.c histo/list_history.c histo/search_history.c \
			  builtin/cd/builtin_cd.c builtin/cd/cd_exec.c builtin/cd/dot_cd.c builtin/cd/list_cd.c builtin/cd/opt_cd.c \
			  builtin/cd/utils_cd.c builtin/test/reverse.c core/init_path_histo.c

#
# Build
#

CC 			= gcc
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
CFLAGS		= -Wall -Wextra -Werror $(addprefix -I, $(INC_DIRS)) -g3
LFLAGS		= -L$(LIB_DIR) -lft -ltermcap
LIB			= libft.a
COMP		= $(CC) $(CFLAGS) -o $@ -c $<
LINK		= $(CC) $(CFLAGS) $(LFLAGS) -o $@ $(filter-out $(LIB_DIR)/$(LIB), $^)
LINKNF		= $(CC) $(CNOFLAGS) $(LFLAGS) -o $@ $(filter-out $(LIB_DIR)/$(LIB), $^)
NUMCORES 	= $(sysctl -n hw.ncpu)
_MAKEFLAGS	= -j$(echo $(NUMCORES)+1| bc) -l$(NUMCORES) -C $(LIB_DIR)

#
# Rules
#

all: $(LIB_DIR)/$(LIB) $(NAME)

debug: CFLAGS += -g3
debug: re

$(LIB_DIR)/$(LIB):
	@make $(_MAKEFLAGS)

$(NAME): $(LIB_DIR)/$(LIB) $(OBJS)
	@$(LINK)
	@echo "completed compilation \033[1;32m√\033[0m"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/core
	@mkdir -p $(OBJS_DIR)/edit_line
	@mkdir -p $(OBJS_DIR)/histo
	@mkdir -p $(OBJS_DIR)/ft_lexer
	@mkdir -p $(OBJS_DIR)/ft_ast
	@mkdir -p $(OBJS_DIR)/hashtable
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/builtin
	@mkdir -p $(OBJS_DIR)/builtin/test
	@mkdir -p $(OBJS_DIR)/builtin/echo
	@mkdir -p $(OBJS_DIR)/builtin/alias
	@mkdir -p $(OBJS_DIR)/builtin/hash
	@mkdir -p $(OBJS_DIR)/builtin/type
	@mkdir -p $(OBJS_DIR)/builtin/set
	@mkdir -p $(OBJS_DIR)/builtin/unset
	@mkdir -p $(OBJS_DIR)/histo/ctrlr_action
	@mkdir -p $(OBJS_DIR)/builtin/export
	@mkdir -p $(OBJS_DIR)/geff
	@mkdir -p $(OBJS_DIR)/armand
	@mkdir -p $(OBJS_DIR)/builtin/jobs
	@mkdir -p $(OBJS_DIR)/builtin/exit
	@mkdir -p $(OBJS_DIR)/builtin/cd
	@$(COMP)

clean:
	@rm $(OBJS) 2> /dev/null || true
	@make $(_MAKEFLAGS) $@
	@rm -rf $(OBJS_DIR)
	@echo "cleaned .o files"

fclean: clean
	@rm $(NAME) 2> /dev/null || true
	@make $(_MAKEFLAGS) $@
	@echo "removed binary"

re: fclean
re: all

.PHONY: all clean fclean re
