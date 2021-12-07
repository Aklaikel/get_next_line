/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 19:09:34 by aklaikel          #+#    #+#             */
/*   Updated: 2021/12/07 19:13:45 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*find_i(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] != '\n')
		i++;
	s = malloc(i + 2);
	i = 0;
	while (str[i] != '\n')
	{	
		s[i] = str[i];
		i++;
	}
	s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

char	*afternewline(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	i++;
	if (str[i] == '\0')
		return (NULL);
	s = malloc(ft_strlen(str) - i + 1);
	while (str[i])
	{
		s[j] = str[i];
		j++;
		i++;
	}
	s[j] = '\0';
	return (s);
}

int	handle_rest(char **buffer, char **str)
{
	char	*tmp;

	if (check_newline(*buffer) >= 0)
	{
		*str = find_i(*buffer);
		tmp = afternewline(*buffer);
		free (*buffer);
		*buffer = tmp;
		return (1);
	}
	else
	{
		*str = *buffer;
		*buffer = NULL;
		return (0);
	}
}

int	handle_ret(char **ret, char **str, char **buffer)
{
	char	*tmp;
	char	*tmp2;

	if (check_newline(*ret) >= 0)
	{
		tmp = find_i(*ret);
		if (*str == NULL)
			*str = tmp;
		else
		{
			tmp2 = ft_strjoin(*str, tmp);
			free(*str);
			free(tmp);
			*str = tmp2;
		}
		*buffer = afternewline(*ret);
		return (free(*ret), 1);
	}
	tmp = ft_strjoin(*str, *ret);
	free(*str);
	*str = tmp;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer[10240];
	char		*ret;
	char		*str;
	int			i;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd] && *buffer[fd])
		if (handle_rest(&buffer[fd], &str))
			return (str);
	ret = (char *)malloc(BUFFER_SIZE + 1);
	if (!ret)
		return (NULL);
	i = read(fd, ret, BUFFER_SIZE);
	while (i > 0)
	{
		ret[i] = '\0';
		if (handle_ret(&ret, &str, &buffer[fd]))
			return (str);
		i = read(fd, ret, BUFFER_SIZE);
	}
	return (free(ret), str);
}
