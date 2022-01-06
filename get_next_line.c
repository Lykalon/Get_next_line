/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykalon <lykalon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:12:23 by lykalon           #+#    #+#             */
/*   Updated: 2022/01/06 14:12:29 by lykalon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		if (was_red < 1)
			break ;
		tmp = ft_strdup(tmp, buf, was_red);
	}
	free(buf);
	new_line = ft_make_line(tmp, was_red);
	tmp = ft_apndx(tmp, new_line);
	return (new_line);
}
