#ifndef FC_H
# define FC_H

#include "sh.h"


# define FC_EDIT_PATH "/usr/bin/vim"
# define FC_EDIT_EDITOR "vim"
# define PATH_TMP ".tmp_fc"

int     check_if_alpha(t_42sh *sh);
int     check_if_digit(t_42sh *sh);
void    print_delimit_history(t_42sh *sh, int start, int stop);
void    edit_last_command(t_42sh *sh);

#endif