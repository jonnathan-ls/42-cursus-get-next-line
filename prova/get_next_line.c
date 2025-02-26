
#include "get_next_line.h"

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return i;
}

char *ft_strdup(char *str)
{
	int i = 0;
	int str_len = ft_strlen(str);
	char *str_cpy = (char *)malloc(sizeof(char) * str_len + 1);
	while(str[i])
	{
		str_cpy[i] = str[i];
		i++;
	}
	return str_cpy;
}

char *ft_strjoin(char *dst, char *src)
{
	int i = 0;
	if (!dst)
		return src;
	if (!src)
		return dst;
	int str_len = ft_strlen(dst) + ft_strlen(src);
	char *str = (char *)malloc(sizeof(char) * str_len + 1);
	while (dst[i])
	{
		str[i] = dst[i];
		i++;
	}
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = NULL_CHAR;
	return str;
}

int ft_has_new_line_chr(char *str)
{
	int i = 0;
	if (!str)
		return 0;
	while (str[i])
	{
		if (str[i] == NEW_LINE)
			return 1;
		i++;
	}
	return 0;
}

void extract_content(char *content, int fd)
{
	char *buf;
	char *temp;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	ssize_t bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == 0)
	{
		free(buf);
		return ;
	}
	temp = content;
	content = ft_strjoin(content, buf);
	free(temp);

	int has_new_line = ft_has_new_line_chr(content);
	if (has_new_line)
	{
		free(buf);
		return ;
	}
	extract_content(content, fd);
	free(buf);
}

char	*get_next_line(int fd)
{
	static char *backup = NULL;
	char *line;
	char *temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	if (!backup)
		backup = ft_strdup(EMPTY_STRING);
	extract_content(backup, fd);
	int line_size = 0;
	while (backup[line_size] && backup[line_size] != NEW_LINE)
		line_size++;
	line = (char *)malloc(sizeof(char) * line_size + 1);
	int i = 0;
	while (i < line_size)
	{
		line[i] = backup[i];
		i++;
	}
	line[i] = NULL_CHAR;
	temp = backup;
	backup = ft_strdup(backup + line_size);
	free(temp);
	return line;
}