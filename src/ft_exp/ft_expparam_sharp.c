/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expparam_sharp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:06:39 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:09:22 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				ft_expparam_sharp_noparam(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*var;
	size_t		param_len;
	int			i;

	param_len = ft_strlen(expparam->word);
	i = 0;
	if (!expparam->word || param_len != 1 || !ft_get_spparam(expparam->word[0]))
	{
		if (expparam->word && (ft_isalpha(expparam->word[0])
			|| expparam->word[0] == '_'))
			while (ft_isalpha(expparam->word[i]) || expparam->word[i] == '_')
				i++;
		if (i == 0 || i != (int)param_len)
		{
			ft_expparam_free(expparam);
			return (ft_exp_brace_error(txt));
		}
	}
	var = ft_getvar(expparam->word, shell);
	param_len = var ? ft_strlen(var) : 0;
	txt->data = ft_itoa((int)param_len);
	free(var);
	ft_expparam_free(expparam);
	return (0);
}

char			*ft_match_rmslprefix(char *param, char *word)
{
	t_matchlist	*list;
	char		*ret;
	int			i;

	list = ft_revmatch(ft_getmatch_list(word));
	ft_strrev(param);
	ret = NULL;
	i = 0;
	while (param[i])
		i++;
	while (!ret)
	{
		if (g_matchtab[list->token](param + i, list))
			ret = ft_strsub(param, 0, i);
		else if (!i)
			ret = ft_strdup(param);
		i--;
	}
	ft_strrev(ret);
	ft_getmatch_free(list);
	return (ret);
}

int				ft_expparam_sharp(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*tmp;

	if (!expparam->param)
		return (ft_expparam_sharp_noparam(txt, shell, expparam));
	if (!(tmp = ft_expanse_word(expparam->word, shell)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	free(expparam->word);
	expparam->word = tmp;
	tmp = ft_getvar(expparam->param, shell);
	if (!tmp)
		tmp = ft_strdup("");
	free(expparam->param);
	expparam->param = tmp;
	txt->data = ft_match_rmslprefix(expparam->param, expparam->word);
	ft_expparam_free(expparam);
	return (0);
}

char			*ft_match_rmlgprefix(char *param, char *word)
{
	t_matchlist	*list;
	char		*ret;
	int			i;

	list = ft_revmatch(ft_getmatch_list(word));
	ft_strrev(param);
	ret = NULL;
	i = 0;
	while (!ret)
	{
		if (g_matchtab[list->token](param + i, list))
			ret = ft_strsub(param, 0, i);
		else if (!param[i])
			ret = ft_strdup(param);
		i++;
	}
	ft_strrev(ret);
	ft_getmatch_free(list);
	return (ret);
}

int				ft_expparam_dsharp(t_txtlist *txt, t_42sh *shell,
				t_expparam *expparam)
{
	char		*tmp;

	if (!expparam->param || !(tmp = ft_expanse_word(expparam->word, shell)))
	{
		ft_expparam_free(expparam);
		return (ft_exp_brace_error(txt));
	}
	free(expparam->word);
	expparam->word = tmp;
	tmp = ft_getvar(expparam->param, shell);
	if (!tmp)
		tmp = ft_strdup("");
	free(expparam->param);
	expparam->param = tmp;
	txt->data = ft_match_rmlgprefix(expparam->param, expparam->word);
	ft_expparam_free(expparam);
	return (0);
}
