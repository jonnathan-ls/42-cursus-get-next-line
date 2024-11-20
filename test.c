
# include <unistd.h>
# include	<stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define NEW_LINE '\n'
# define NULL_CHAR '\0'
# define EMPTY_STRING ""

size_t ft_strlen(const char *s)
{
	int len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *src)
{
	int		src_size;
	char	*str_cpy;
	int	i;

	src_size = ft_strlen(src);
	str_cpy = (char *)malloc(src_size + 1);
	i = 0;
	while (src[i])
	{
		str_cpy[i] = src[i];
		i++;
	}
	str_cpy[i] = '\0';
	return (str_cpy);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	substr_len;
	char	*substr;

	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
		substr_len = 0;
	else if (start + len > s_len)
		substr_len = s_len - start;
	else
		substr_len = len;
	substr = (char *)malloc(substr_len + 1);
	if (substr)
	{
		while (i < len && start + i < s_len)
		{
			substr[i] = s[start + i];
			i++;
		}
		substr[i] = '\0';
	}
	return (substr);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	s1_size;
	size_t	s2_size;
	char	*joined_str;

	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	joined_str = (char *)malloc(s1_size + s2_size + 1);
	if (joined_str)
	{
		while (i < s1_size)
		{
			joined_str[i] = s1[i];
			i++;
		}
		while (i - s1_size < s2_size)
		{
			joined_str[i] = s2[i - s1_size];
			i++;
		}
		joined_str[i] = '\0';
	}
	return (joined_str);
}

char *get_next_line(int fd)
{
	static char *backup;
	char *buffer;;
	char *line;
	int index = 0;
	int bytes_read = 0;
	char *tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return NULL;

	if (!backup)
		backup	= ft_strdup(EMPTY_STRING);

	while (!ft_strchr(backup, NEW_LINE))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(backup);
			backup = NULL;
			return (NULL);
		}
		else if (bytes_read	== 0)
			break;
		buffer[bytes_read] = NULL_CHAR;
		tmp = backup;
		backup = ft_strjoin(backup, buffer);
		free(tmp);
	}
	index = 0;
	if (backup[index] == NULL_CHAR)
	{
		free(buffer);
		free(backup);
		backup = NULL;
		return NULL;
	}

	while (backup[index] && backup[index] != '\n')
		index++;
	
	if (backup[index] && backup[index] == '\n')
		index++;
	line = ft_substr(backup, 0, index);
	if (!line)
	{
		free(backup);
		return NULL;
	}
	
	tmp = backup;
	backup = ft_strdup(backup + index);
	free(tmp);
	free(buffer);
	return line;
}

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main()
{
	int fd = open("gnlTester/files/multiple_line_no_nl", O_RDONLY);
	if (fd < 0)
		return 1;

	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		// int r = strcmp(line, "\n");
		// printf("	| %d\n", r);
		free(line);
	}

	close(fd);
	return 0;
}