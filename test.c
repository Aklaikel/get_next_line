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
	static char	*buffer;
	char		*ret;
	char		*tmp;
	char		*line;
	int 		i;
	
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer && *buffer)
	{
		if (check_newline(buffer) >= 0)
		{
			line = find_i(buffer);
			buffer = afternewline(buffer);
			return (line);
		}
		else
		{
			line = buffer;
			buffer = NULL;
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
			if (line == NULL)
				line = tmp;
			else
			{
				line = ft_strjoin(line, tmp);
				free(tmp);
			}
			buffer = afternewline(ret);
			return (free(ret), line);
		}
		if (line == NULL)
			line = ft_strdup(ret);
		else
			line = ft_strjoin(line, ret);
		i = read(fd, ret, BUFFER_SIZE);
	}
	return (free (ret), line);
}
/*
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
}*/
