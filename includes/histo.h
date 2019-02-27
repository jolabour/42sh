#ifndef HISTO_H
# define HISTO_H

#include "sh.h"

typedef struct		s_history
{
	char			*str;
	struct s_history *next;
	struct s_history *prev;
}					t_history;

typedef struct		s_history_mark
{
	t_history		*begin;
	t_history		*last;
	t_history		*cur;
	char 			*last_str;
	int				error_code;
	char			*ctrlr_arg;
	int				is_find;
	int 			pos_arg;
	int				pos;
	int				size;
	int				cursor_pos;
	int				line_pos;
	int				nb_moove;
	int				dup_select;
	//fc//
	int				print_nb_line;
	int 			reverse_print;
}					t_history_mark;

int					check_following(char *to_find, char *search, int start_search, int len_check);
int 				check_after(char *arg, char *dup, int i2, int len_arg);
void				clean_line_lentoback();

#endif