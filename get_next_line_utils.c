/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:50:44 by aklaikel          #+#    #+#             */
/*   Updated: 2021/12/07 01:31:42 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	join(char *dest, char *src, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		str[i] = dest[i];
		i++;
	}
	while (src[j] != '\0')
	{
		str[i + j] = src[j];
		j++;
	}
	str[i + j] = '\0';
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = (char *)malloc(sizeof(char ) * (ft_strlen((char *)s1) + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	total;

	if (s1 == NULL)
		return (ft_strdup(s2));
	total = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (total + 1));
	if (!str)
		return (NULL);
	join(s1, s2, str);
	//if (s1)
	//	free(s1);
	return (str);
}


int check_newline(char *ret)
{
	int i;
	
	i = 0;
	if (!ret)
		return (-1);
	while (ret[i] != '\n' && ret[i] != '\0')
		i++;
	if (ret[i] == '\n')
		return (i);
	return(-1);
}
