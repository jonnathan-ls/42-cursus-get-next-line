
#include "get_next_line.h"

int ft_strlen(char *str)
{
	int i = 0;
	if (!str)
		return i;
	while (str[i])
		i++;
	return i;
}

char *ft_strdup(char *str)
{
	int i = 0;
	char *str_cpy;
	if (!str)
		return NULL;
	while (str[i])
		i++;
	str_cpy = (char *)malloc(sizeof(char) * i + 1);
	if (!str_cpy)
		return NULL;
	i = 0;
	while (str[i])
	{
		str_cpy[i] = str[i];
		i++;
	}
	str_cpy[i] = NULL_CHAR;
	return str_cpy;
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	index;
	size_t	s1_size;
	size_t	s2_size;
	char	*joined_str;

	index = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	joined_str = (char *)malloc(s1_size + s2_size + 1);
	if (joined_str)
	{
		while (index < s1_size)
		{
			joined_str[index] = s1[index];
			index++;
		}
		while (index - s1_size < s2_size)
		{
			joined_str[index] = s2[index - s1_size];
			index++;
		}
		joined_str[index] = '\0';
	}
	return (joined_str);
}

bool has_breakline_chr(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == BREAKLINE_CHAR)
			return (true);
		i++;
	}
	return false;
}

void read_content(char **buffer, t_gnl *gnl, int fd)
{
	*buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	int bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read == 0)
		gnl->is_eof = true;
	gnl->content_length += bytes_read;
	(*buffer)[bytes_read] = NULL_CHAR;
}


void extract_line(t_gnl *gnl)
{
	int line_size = 0;
	while (gnl->content[line_size] && gnl->content[line_size] != BREAKLINE_CHAR)
		line_size++;
	if (gnl->content[line_size] == BREAKLINE_CHAR)
		line_size++;
	gnl->line = (char *)malloc(sizeof(char) * (line_size + 2));
	if (!gnl->line)
		return ;
	int i = 0;
	while (i < line_size)
	{
		gnl->line[i] = gnl->content[i];
		i++;
	}
	if (gnl->content[i] == NULL_CHAR)
	{
		gnl->line[i] = BREAKLINE_CHAR;
		gnl->line[i + 1] =NULL_CHAR;
	}
	else
		gnl->line[i] = NULL_CHAR;
	gnl->content_length -= i;
	char *temp = gnl->content;
	gnl->content = ft_strdup(gnl->content + line_size);
	free(temp);
}

char *gnl(int fd)
{
	// struct estatico para guardar content, eof e has_content
	// se content for null inicializa
	// if for eof e nao tiver mais conteúdo retorna libera content e retorna null
	// if nao for eof e content nao conter breakline
	// entra em loop para
	//		ler a o conteudo com base no tamanho do buffer
	//		atualiza conteudo 
	//		libera alocacoes dinamicas
	//		interrompe o laco se for eof ou encontrar quebra de lihnha
	// extrai a linha realizando
	//		calculo do tamanho da linha
	//		alocando memoria
	//		faz a copia dos caracteres
	//		adiciona quebra de linha
	//		atualiza content e has_content
	// retorna linha

	static t_gnl gnl;
	
	char *buffer;

	if(!gnl.content)
		gnl.content = ft_strdup(EMPTY_STRING);
	if (gnl.is_eof && gnl.content_length <= 0)
	{
		if (gnl.content)
			free(gnl.content);
		return NULL;
	}
	if (!gnl.is_eof && !has_breakline_chr(gnl.content))
	{
		while (true)
		{
			read_content(&buffer, &gnl, fd);

			char *temp = gnl.content;
			gnl.content = ft_strjoin(gnl.content, buffer);
			free(temp);
			free(buffer);
			if (gnl.is_eof || has_breakline_chr(gnl.content))
				break;
		}
	}
	extract_line(&gnl);
	if (!gnl.line)
	{
		free(gnl.content);
		return (NULL);
	}
	return gnl.line;
}


// TODO: Remover
#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	char *line;

	int fd = open("content", 'r');
	while (true)
	{
		line = gnl(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	close(fd);
}