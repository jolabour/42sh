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
			  core/init_shell.c utils/errno.c edit_line/prompt.c \
			  edit_line/stdin.c edit_line/move_arrows.c edit_line/manip_input.c \
			  edit_line/insert_mode.c edit_line/move_word.c \
			  edit_line/control_action.c edit_line/keymap.c \
			  hashtable/hashtable.c edit_line/keymap_select.c \
			  hashtable/init_hashtable.c utils/ft_joinpath.c utils/env.c \
			  edit_line/select_mode.c edit_line/move_select_mode.c \
			  edit_line/action_select_mode.c edit_line/move_line.c \
			  geff/main.c geff/ft_lexer.c geff/ft_ast.c \
			  histo/init_file_history.c histo/parser_history.c \
			  edit_line/move_histo.c histo/substitute_history.c \
			  builtin/test/test.c builtin/test/test_bcdef.c builtin/test/test_glprS.c \
			  builtin/test/test_suwxz.c builtin/echo/echo.c substitution/parser_substitution.c \
			  builtin/tabulation/tabulation.c builtin/alias/alias.c \
			  builtin/test/exec_other.c builtin/test/test_other.c builtin/alias/unalias.c \
			  builtin/hash/hash.c builtin/type/type.c histo/ctrlr_action/utils_ctrlr.c \
			  histo/ctrlr_action/get_line_ctrlr.c histo/ctrlr_action/place_curs_ctrlr.c \
			  histo/ctrlr_action/prompt_ctrlr.c  histo/ctrlr_action/back_in_history.c \
			  builtin/fc/builtin_fc.c builtin/fc/check_int_char.c builtin/fc/edit_last_command.c \
			  histo/ctrlr_action/ctrlr_action.c builtin/set/set.c builtin/unset/unset.c builtin/export/export.c

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
	@mkdir -p $(OBJS_DIR)/lexer
	@mkdir -p $(OBJS_DIR)/hashtable
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/builtin
	@mkdir -p $(OBJS_DIR)/builtin/test
	@mkdir -p $(OBJS_DIR)/builtin/echo
	@mkdir -p $(OBJS_DIR)/builtin/tabulation
	@mkdir -p $(OBJS_DIR)/substitution
	@mkdir -p $(OBJS_DIR)/builtin/alias
	@mkdir -p $(OBJS_DIR)/builtin/hash
	@mkdir -p $(OBJS_DIR)/builtin/type
	@mkdir -p $(OBJS_DIR)/builtin/fc
	@mkdir -p $(OBJS_DIR)/builtin/set
	@mkdir -p $(OBJS_DIR)/builtin/unset
	@mkdir -p $(OBJS_DIR)/histo/ctrlr_action
	@mkdir -p $(OBJS_DIR)/builtin/export
	@mkdir -p $(OBJS_DIR)/geff
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
