/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:45:41 by geargenc          #+#    #+#             */
/*   Updated: 2019/04/12 14:45:47 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*ft_getvar(char *var, t_42sh *shell)
{
	void	*ptr;
	char	*varenv;

	ptr = ft_get_spparam(*var);
	if (ptr)
		return (((char *(*)(t_42sh *))ptr)(shell));
	varenv = ft_strjoin(var, "=");
	ptr = ft_getenv(shell->env, varenv, ft_strlen(varenv), NULL);
	free(varenv);
	if (ptr)
		return (ft_strdup(ptr));
	ptr = get_var(shell, var);
	if (ptr)
		return ((char *)ptr);
	return (NULL);
}
