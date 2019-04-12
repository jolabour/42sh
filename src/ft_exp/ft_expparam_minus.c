/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_minus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:45:09 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 13:46:04 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_expparam_cnminus(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*word;

	if (!expparam->param || !(word = ft_expanse_word(expparam->word, shell)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	free(expparam->word);
	expparam->word = word;
	txt->data = ft_getvar(expparam->param, shell);
	if (txt->data && !txt->data[0])
	{
		free(txt->data);
		txt->data = NULL;
	}
	if (txt->data)
		txt->data = ft_backslash_quotes(txt->data, txt->dquote);
	else
	{
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	ft_expparam_free(expparam);
	return (0);
}

int				ft_expparam_minus(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*word;

	if (!expparam->param || !(word = ft_expanse_word(expparam->word, shell)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	free(expparam->word);
	expparam->word = word;
	txt->data = ft_getvar(expparam->param, shell);
	if (txt->data)
		txt->data = ft_backslash_quotes(txt->data, txt->dquote);
	else
	{
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	ft_expparam_free(expparam);
	return (0);
}
