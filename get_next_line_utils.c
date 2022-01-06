long	ft_strlen(char *s)
{
	long	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

//void	ft_strncpy(char *src, char *dest, long n)
//{
//	;
//}
//
//ft_format()
//{
//	char	*format;
//
//	return (format);
//}
