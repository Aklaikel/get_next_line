/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:16:36 by aklaikel          #+#    #+#             */
/*   Updated: 2021/12/04 19:08:26 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *find_i(char *str)
{
	int i;
	char *s;
	
	i = 0;
	while(str[i] != '\n')
		i++;
	s = malloc(i + 2);
	i = 0;
	while(str[i] != '\n')
	{	
		s[i] = str[i];
		i++;
	}
	s[i++] = '\n';
	s[i] = '\0';
	return(s);
}

char *afternewline(char *str)
{
	int i;
	int j;
	char *s;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	i++;
	if(str[i] == '\0')
		return (NULL);
	s =	malloc(ft_strlen(str) - i + 1);
	while (str[i])
	{
		s[j] = str[i];
		j++;
		i++;
	}
	s[j] = '\0';
	// free(str);
	return (s);
}

char *get_next_line(int fd)
{
	static char	*shi;
	char		*ret;
	char		*tmp;
	char		*str;
	int 		i;
	
	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (shi && *shi)
	{
		if (check_newline(shi) >= 0)
		{
			str = find_i(shi);
			shi = afternewline(shi);
			return (str);
		}
		else
		{
			str = shi;
			shi = NULL;
		}
	}
	ret = (char *)malloc(BUFFER_SIZE + 1);
	if (!ret)
		return (NULL);
	i = read(fd, ret, BUFFER_SIZE);
	while (i > 0)
	{
		ret[i] = '\0';
		if (check_newline(ret) >= 0)
		{
			tmp = find_i(ret);
			if (str == NULL)
				str = tmp;
			else
			{
				str = ft_strjoin(str, tmp);
				free(tmp);
			}
			shi = afternewline(ret);
			free(ret);
			return (str);
		}
		if (str == NULL)
			str = ft_strdup(ret);
		else
			str = ft_strjoin(str, ret);
		i = read(fd, ret, BUFFER_SIZE);
	}
	free(ret);
	return (str);
	/*
	i = read(fd, ret, BUFFER_SIZE);
	if (i == 0 && shi && *shi)
	{
		str = shi;
		shi = NULL;
		return (free(ret), str);
	}
	if (i <= 0)
		return (free(ret), NULL);
	ret[i] = '\0';
	if(!shi)
		shi = ft_strdup(ret);	
	else
		shi = ft_strjoin(shi, ret);
	if (check_newline(shi) >= 0)
	{
		write(1,"k\n", 2);
		str = find_i(shi);
		shi = afternewline(shi);
	}
	else
		return (free(ret), get_next_line(fd));
	return (free(ret), str);
	*/
}

int main()
{
	int fd = open("text.txt", O_RDONLY);
	char *r;
	
	r = NULL;
	while((r = get_next_line(fd)))
	{
		printf("%s", r);
		free(r);
	}
}