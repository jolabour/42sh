/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:53:55 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/20 05:48:11 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_expparam_cnplus(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*word;

	if (!expparam->param || !(word = ft_simple_expanse(expparam->word, shell)))
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
	{
		free(txt->data);
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	else
		txt->data = ft_strdup("");
	ft_expparam_free(expparam);
	return (0);
}

int				ft_expparam_plus(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*word;

	if (!expparam->param || !(word = ft_simple_expanse(expparam->word, shell)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	free(expparam->word);
	expparam->word = word;
	txt->data = ft_getvar(expparam->param, shell);
	if (txt->data)
	{
		free(txt->data);
		txt->data = ft_backslash_quotes(expparam->word, txt->dquote);
		expparam->word = NULL;
	}
	else
		txt->data = ft_strdup("");
	ft_expparam_free(expparam);
	return (0);
}
