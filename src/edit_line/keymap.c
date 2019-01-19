# include "sh.h"

const long			input_tab[NB_INPUT] = {RIGHT_KEY, LEFT_KEY, DEL, CTRL_C, CTRL_D, HOME, END, OPT_B, OPT_F, OPT_C, OPT_X, OPT_V, OPT_UP, OPT_DOWN, UP_KEY, DOWN_KEY};

const t_ak			action_tab[NB_INPUT] = {move_to_right, move_to_left, delete_input_buf, ctrlc_action, ctrld_action, move_to_start, move_to_end, move_to_begin_word, move_to_end_word, select_mode, select_mode, ft_paste, move_up, move_down, up_histo, down_histo};

void				up_input(t_42sh *sh)
{
	char			*tmp;

	tmp = ft_strdup(sh->stdin->input);
	ft_strdel(&sh->stdin->input);
	sh->stdin->size_of_input = sh->stdin->size_of_input * 2;
	if (!(sh->stdin->input = malloc(sizeof(char) * sh->stdin->size_of_input)))
		print_error(_ENOMEM, 1);
	ft_strcpy(sh->stdin->input, tmp);
	ft_strdel(&tmp);
}

int					check_input(t_42sh *sh, long buf)
{
	int			i;

	i = 0;
	while (i < NB_INPUT)
	{
		if (input_tab[i] == buf)
		{
			action_tab[i](sh);
			if (i == 3)
				return (-1);
			if (i == 9 || i == 10 || i == 11)
				return (2);
			return (1);
		}
		i++;
	}
	if (sh->stdin->len_line >= sh->stdin->size_of_input - 10)
		up_input(sh);
	sh->winsize = get_winsize();
	add_char(buf, sh);
	sh->stdin->len_line++;
	free(sh->history_mark->cur->str);
	sh->history_mark->cur->str = ft_strdup(sh->stdin->input);
	move_to_right(sh);
	clean_print(sh);
	return (0);
}
