
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
	if (!str)
		return NULL;
	int str_len = ft_strlen(str);
	char *str_cpy = (char *)malloc(sizeof(char) * str_len + 1);
	while(str[i])
	{
		str_cpy[i] = str[i];
		i++;
	}
	str_cpy[i] = NULL_CHAR;
	return str_cpy;
}

char *ft_strjoin(char *dst, char *src)
{
	int i = 0;
	int j = 0;
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
	while (src[j])
	{
		str[i + j] = src[j];
		j++;
	}
	str[i + j] = NULL_CHAR;
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

// void extract_content(char *content, int fd)
// {
// 	char *buf;
// 	char *temp;

// 	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
// 	ssize_t bytes_read = read(fd, buf, BUFFER_SIZE);
// 	if (bytes_read == 0)
// 	{
// 		free(buf);
// 		return ;
// 	}
// 	temp = content;
// 	content = ft_strjoin(content, buf);
// 	free(temp);

// 	int has_new_line = ft_has_new_line_chr(content);
// 	if (has_new_line)
// 	{
// 		free(buf);
// 		return ;
// 	}
// 	extract_content(content, fd);
// 	free(buf);
// }


// Le do fd a quantidade de bytes padrao
// verifica se e eof
// se for eof, verifica	se o backup tem \n
// se tiver, retorna a linha ate o \n
// atualiza o backup com o restante do conteudo
// se nao tiver, retorna o backup
// se nao for eof, concatena o conteudo lido com o backup
// verifica se o backup tem \n
// se tiver, retorna a linha ate o \n
// se nao tiver, repete o processo
// apos retornar a linha, atualiza o backup com o restante do conteudo
// retorna a linha

int ft_strchr(char *str, char chr)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == chr)
			return 1;
		i++;
	}
	return 0;
}

char *extract_line(char *content)
{
	int i = 0;
	char *line;
	while (content[i] && content[i] != NEW_LINE)
		i++;
	if (ft_has_new_line_chr(content))
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (content[i] && content[i] != NEW_LINE)
	{
		line[i] = content[i];
		i++;
	}
	if (ft_has_new_line_chr(content))
	{
		line[i] = NEW_LINE;
		i++;
	}
	line[i] = NULL_CHAR;
	return line;
}

char *update_backup(char *content, char *line)
{
	int line_len = ft_strlen(line);
	char *temp = content;
	content = ft_strdup(content + line_len);
	free(temp);
	return content;
}


char	*get_next_line(int fd)
{
	static char *backup;
	char *line;
	char *temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	temp = (char *)malloc(sizeof(char) * BUFFER_SIZE	+ 1);
	int byes_read = read(fd, temp, BUFFER_SIZE);
	int is_eof = byes_read == 0;
	if (is_eof)
	{
		if (ft_has_new_line_chr(backup))
		{
			line	= extract_line(backup);
			backup = update_backup(backup, line);
			free(temp);
			return line;
		}
		else
		{
			line = ft_strdup(backup);
			free(backup);
			backup = NULL;
			free(temp);
			return line;
		}
	}
	temp[byes_read] = NULL_CHAR;
	if (!backup)
		backup = ft_strdup(EMPTY_STRING);
	backup = ft_strjoin(backup, temp);
	if (ft_has_new_line_chr(backup))
	{
		line = extract_line(backup);
		backup = update_backup(backup, line);
		free(temp);
		return line;
	}
	line = get_next_line(fd);
	free(temp);
	return line;
}