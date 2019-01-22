/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 22:54:23 by jolabour          #+#    #+#             */
/*   Updated: 2019/01/22 01:27:01 by jolabour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			substitute_param(t_42sh *sh)
{
	char		*substitute;

	if (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str + 2] == '?' && sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str + 3] == '}')
	{
		substitute = ft_itoa(sh->argv->error_code);
		get_substitute(sh, 4, substitute);
		sh->argv->pos_str = sh->argv->pos_str + ft_strlen(substitute);
		ft_strdel(&substitute);
	}
}

void			dollar_substitute(t_42sh *sh)
{
	if (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str + 1] == '{')
		substitute_param(sh);
	//if (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str + 1] == '(' && sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str + 2] == '(')
	//	substitute_arithmetic(sh);
}

void			check_substitute(t_42sh *sh)
{
	sh->argv->cur_str = 0;
	//check_alias(sh);
	while (sh->argv->argv[sh->argv->cur_str] != NULL)
	{
		sh->argv->pos_str = 0;
		while (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str] != '\0')
		{
			if (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str] == '$')
				dollar_substitute(sh);
			//if (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str] == '!')
			//	histo_substitution(sh);
			//if (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str] == '~')
			//	tilde_substitution(sh);
			else
				sh->argv->pos_str++;
		}
		sh->argv->cur_str++;
	}
}
