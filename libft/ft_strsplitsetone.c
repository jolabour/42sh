#include <stdlib.h>
#include "libft.h"

size_t				check_delim(const char *str, char c)
{
	size_t			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char			**ft_strsplitsetone(char const *s, char delim)
{
	char		**split;
	size_t		len;

	len = check_delim(s, delim);
	if (!(split = malloc(sizeof(char*) * 3)))
		return (NULL);
	if (len >= ft_strlen(s))
	{
		split[0] = ft_strsub(s, 0, len);
		split[1] = ft_strdup("\0");
	}
	else if (len == 0)
	{
		split[0] = ft_strdup("\0");
		split[1] = ft_strsub(s, 1, ft_strlen(s) - 1);
	}
	else
	{
		split[0] = ft_strsub(s, 0, len);
		split[1] = ft_strdup(s + len + 1);
	}
	split[2] = NULL;
	return (split);
}
