#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	
	char *tmp;
	static char *str;
	int i;
	char buf[BUFF_SIZE];

	if (fd < 0 || !line)
		return (-1);
	if (!str)
		str = ft_strnew(BUFF_SIZE);
	while (!(ft_strchr(str, '\n')))
	{
		if ((i = read(fd, buf, BUFF_SIZE)) < 1)
		{
			if (i < 0)
				return (-1);
			if (ft_strlen(str) > 0)
			{
				*line = ft_strdup(str);
				ft_strdel(&str);
				return (1);
			}
			*line = NULL;
			return (0);
		}
		buf[i] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, buf);
		ft_strdel(&tmp);
	}
	*line = ft_strsub(str, 0, (ft_strchr(str, '\n') - str));
	if (ft_strchr(str, '\n'))
		ft_strcpy(str, ft_strchr(str, '\n') + 1);
	return (1);
}
