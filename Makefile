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
			  ft_exe/ft_exe_assigns.c ft_exe/ft_exe_builtin.c \
			  ft_exe/ft_exe_command.c ft_exe/ft_exe_compound.c \
			  ft_exe/ft_exe_exit.c ft_exe/ft_exe_file.c \
			  ft_exe/ft_exe_redir.c ft_exe/ft_exe_redirand.c \
			  ft_exe/ft_exe_redirerror.c ft_exe/ft_exe_separators.c \
			  ft_exe/ft_exe_tmpfd.c \
			  ft_jobs/ft_jobs_any.c ft_jobs/ft_jobs_check.c \
			  ft_jobs/ft_jobs_cmdline1.c ft_jobs/ft_jobs_cmdline2.c \
			  ft_jobs/ft_jobs_error.c ft_jobs/ft_jobs_get.c \
			  ft_jobs/ft_jobs_launch.c ft_jobs/ft_jobs_manage.c \
			  ft_jobs/ft_jobs_remove.c ft_jobs/ft_jobs_report.c \
			  ft_jobs/ft_jobs_signals.c ft_jobs/ft_jobs_status.c \
			  ft_jobs/ft_jobs_tools.c \
			  geff/ft_expanse.c \
			  histo/init_file_history.c histo/parser_history.c \
			  edit_line/move_histo.c histo/substitute_history.c \
			  builtin/test/test.c builtin/test/test_bcdef.c builtin/test/test_glprs.c \
			  builtin/test/test_suwxz.c builtin/test/test_l.c builtin/echo/echo.c  \
			  builtin/alias/alias.c  builtin/alias/list_alias.c \
			  builtin/test/exec_other.c builtin/test/test_other.c builtin/alias/unalias.c \
			  builtin/hash/hash.c builtin/type/type.c builtin/type/print_type.c histo/ctrlr_action/utils_ctrlr.c \
			  histo/ctrlr_action/get_line_ctrlr.c histo/ctrlr_action/place_curs_ctrlr.c \
			  histo/ctrlr_action/prompt_ctrlr.c  histo/ctrlr_action/back_in_history.c \
			  builtin/fc/builtin_fc.c builtin/fc/check_int_char.c builtin/fc/edit_last_command.c \
			  histo/ctrlr_action/ctrlr_action.c builtin/set/set.c builtin/unset/unset.c builtin/export/export.c armand/ft_check_exp_ari.c armand/ft_erase_space.c builtin/export/print_export.c \
			  armand/ft_logic_op.c armand/ft_true_op.c armand/ft_check_var.c armand/ft_itoa_exp_ari.c \
			  armand/ft_math_op.c armand/exp_ari.c builtin/unset/list_unset.c \
			  builtin/jobs/jobs.c builtin/jobs/fg.c builtin/jobs/bg.c \
			  builtin/exit/exit.c utils/ft_continue_line.c utils/ft_get_opts.c \
			  utils/tools.c utils/var.c utils/check.c histo/list_history.c histo/search_history.c \
			  builtin/cd/builtin_cd.c builtin/cd/cd_exec.c builtin/cd/dot_cd.c builtin/cd/list_cd.c builtin/cd/opt_cd.c \
			  builtin/cd/utils_cd.c

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
	@mkdir -p $(OBJS_DIR)/ft_ast
	@mkdir -p $(OBJS_DIR)/ft_exe
	@mkdir -p $(OBJS_DIR)/ft_jobs
	@mkdir -p $(OBJS_DIR)/ft_lexer
	@mkdir -p $(OBJS_DIR)/hashtable
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/builtin
	@mkdir -p $(OBJS_DIR)/builtin/test
	@mkdir -p $(OBJS_DIR)/builtin/echo
	@mkdir -p $(OBJS_DIR)/builtin/alias
	@mkdir -p $(OBJS_DIR)/builtin/hash
	@mkdir -p $(OBJS_DIR)/builtin/type
	@mkdir -p $(OBJS_DIR)/builtin/fc
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
