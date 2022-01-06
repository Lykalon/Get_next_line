#include "get_next_line.h"

//#define BUFFER_SIZE 42

long	ft_strlen(char *s);
int		ft_find_nl(char *s);

char	*ft_apndx(char *tmp, char *new_line)
{
	char	*s;
	int		i;
	long	apndx;

	if (new_line == NULL)
		return (0);
	if (ft_strlen(tmp) == ft_strlen(new_line))
	{
		free(tmp);
		return (0);
	}
	apndx = ft_strlen(tmp) - ft_strlen(new_line) + 1;
	s = malloc(apndx);
	i = 0;
	while (i < apndx)
	{
		s[i] = tmp[ft_strlen(new_line) + i];
		i++;
	}
	free(tmp);
	return (s);
}

//char	*ft_apndx(char *tmp, long was_red)
//{
//	char	*s;
//	int		nl_index;
//	long	len;
//	int		i;
//
//	if (was_red == -1 || tmp == NULL)
//		return (0);
//	if (was_red == 0 && ft_find_nl(tmp) == -1)
//	{
//		free(tmp);
//		return (0);
//	}
//	nl_index = ft_find_nl(tmp);
//	len = ft_strlen(tmp);
//	i = 0;
//	s = malloc(len - nl_index);
//	if (!s)
//		return (0);
//	while (i < len - nl_index)
//	{
//		s[i] = tmp[i + (nl_index + 1)];
//		i++;
//	}
//	free(tmp);
//	return (s);
//}

char	*ft_make_line(char *tmp, long was_red)
{
	char	*s;
	long	end_index;
	int		i;

	end_index = ft_find_nl(tmp) + 1;
	if (was_red == -1 || tmp == NULL)
		return (0);
	if (was_red == 0 && (tmp == NULL || tmp[0] == '\0'))
		return (0);
	else if (was_red == 0 && tmp[0] != '\0' && ft_find_nl(tmp) == -1)
		end_index = ft_strlen(tmp);
	i = 0;
	s = malloc(end_index + 1);
	if (!s)
		return (0);
	while (i < end_index)
	{
		s[i] = tmp[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

//char	*ft_make_line(char *tmp, long was_red)
//{
//	char	*s;
//	long	end_index;
//	int		i;
//
//	if (was_red == -1)
//		return (0);
//	if (was_red == 0 && tmp != NULL && ft_find_nl(tmp) == -1)
//		end_index = ft_strlen(tmp) - 1;
//	else if (was_red == 0 && (tmp == NULL || *tmp == '\0'))
//		return (0);
//	else if (was_red != 0 && ft_find_nl(tmp) == -1)
//		end_index = ft_strlen(tmp) - 1;
//	else
//		end_index = ft_find_nl(tmp);
//	i = 0;
//	s = malloc(end_index + 1);
//	while (i < end_index + 1)
//	{
//		s[i] = tmp[i];
//		i++;
//	}
//	return (s);
//}

char	*ft_strdup(char *tmp, char *buf, long was_red)
{
	char	*s;
	long	len;
	int		i;

	i = 0;
	len = ft_strlen(tmp);
	s = malloc(len + was_red + 1);
	if (!s)
		return (0);
	if (tmp != NULL)
	{
		while (i < len)
		{
			s[i] = tmp[i];
			i++;
		}
		free(tmp);
	}
	while (i < len + was_red)
	{
		s[i] = buf[i - len];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_find_nl(char *s)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buf;
	long		was_red;
	char		*new_line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (0);
	while (ft_find_nl(tmp) == -1)
	{
		was_red = read(fd, buf, BUFFER_SIZE);
//		printf("was red: %ld\n", was_red);
		if (was_red < 1)
			break ;
		tmp = ft_strdup(tmp, buf, was_red);
//		printf("tmp: %s\n\n", tmp);
	}
	free(buf);
	new_line = ft_make_line(tmp, was_red);
	tmp = ft_apndx(tmp, new_line);
//	printf("new_line: %s", new_line);
	return (new_line);
}

//int main(void)
//{
//	int fd = open("test", O_RDONLY);
//	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
//}
