/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 07:09:16 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/20 01:06:16 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*ft_strjoinfree(char *s1, char *s2, unsigned int which)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	join = (char *)ft_malloc_exit(i + j + 1);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	if (which == 1 || which > 2)
		free(s1);
	if (which > 1)
		free(s2);
	return (join);
}

int			ft_str_isdigit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int			ft_str_isquote(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' || str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int			ft_chars_in_int(int nbr)
{
	int		count;

	count = (nbr < 0) ? 2 : 1;
	while (nbr > 9 || nbr < -9)
	{
		count++;
		nbr = nbr / 10;
	}
	return (count);
}

char		*ft_strrev(char *str)
{
	char	tmp;
	int		len;
	int		i;

	len = 0;
	while (str[len])
		len++;
	i = 0;
	while (i < len - i - 1)
	{
		tmp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
		i++;
	}
	return (str);
}
