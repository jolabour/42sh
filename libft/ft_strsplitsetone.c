#include <stdlib.h>
#include "libft.h"

int				first_len(const char *str, char c)
{
	int			i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char			**ft_strsplitsetone(char const *s, char delim)
{
	char		**split;
	int			i;
	int			j;
	int			a;

	if (!(split = malloc(sizeof(char*)
					* 3)))
		return (NULL);
	i = 0;
	if (!(split[0] = malloc(sizeof(char) * first_len(s, delim) + 1)))
		return (NULL);
	if (!(split[1] = malloc(sizeof(char) * (ft_strlen(s) - first_len(s, delim)))))
		return (NULL);
	a = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == delim)
		{
			split[a][j] = '\0';
			a++;
			j = 0;
			i++;
		}
		split[a][j] = s[i];
		i++;
		j++;
	}
	split[a][j] = '\0';
	split[2] = NULL;
	return (split);
}
