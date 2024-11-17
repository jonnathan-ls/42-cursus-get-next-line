
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 5
#endif

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *get_next_line(int fd)
{
	// 1 A função vai receber um FD
	// 2 Deve retornar NULL se o FD ou BUFFER_SIZE for menor ou igual a 0
	// 3 Deve retornar NULL se não conseguir alocar memória
	// 4 Deve retornar NULL se não conseguir ler o arquivo
	// 5 Deve ler o arquivo apontado pelo FD com base no BUFFER_SIZE que poderá	ser fornecido
	// 6 Deve processar a leitura do arquivo até	encontrar um '\n' ou EOF
	// 7 A linha retornada deve incluir o '\n' se ele estiver presente, exceto se EOF foi alcançado e nao	há '\n'
	// 9 Toda a memória alocada dinamicamente deve ser liberada
	// 10 O uso de variável estática deve ser limitado em apenas uma
	// 11 Toda leitura de ponteiro deve ser protegido contra segfault
	// 12 A função deve trabalhar com 0, 1 ou N (ex 10000000) de	BUFFER_SIZE
	// 13 A função deve lidar com leitura de FD em arquivo binário
	// 14 A função deve ser capaz de ler múltiplos FDs
	// 15 A função deve ser prototipada da seguinte maneira: char *get_next_line(int fd);
	// 16 lseek, global variables are not allowed
	char *line;
	char *buffer;
	int i;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	i = read(fd, buffer, BUFFER_SIZE);
	if (i <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	line = malloc(sizeof(char) * i + 1);
	if (!line)
	{
		free(line);
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (i < BUFFER_SIZE && buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		if (buffer[i] == '\n')
			break;
		if (i == BUFFER_SIZE - 1)
		{
			int line_size = ft_strlen(line);
			free(line);
			line	= malloc(sizeof(char) * (line_size + BUFFER_SIZE + 1));
			int bytes_readed = read(fd, buffer, BUFFER_SIZE);
			if (bytes_readed <= 0)
			{
				free(buffer);
				free(line);
				return (NULL);
			}
			buffer[i] = '\0';
			i = 0;
		}
		i++;
	}
	// enquanto não encontrar um '\n' ou '\0' ele vai continuar lendo

	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	free(buffer);
	return (line);
}

#include <stdio.h>
int main()
{
	int fd;
	fd = open("text.txt", 'r');

	char *r;
	while	((r = get_next_line(fd)))
	{
		printf("%s\n", r);
		free(r);
	}
	close(fd);
	return (0);
}

// 1 A função vai receber um FD
// 2 Deve retornar NULL se o FD ou BUFFER_SIZE for menor ou igual a 0
// 3 Deve retornar NULL se não conseguir alocar memória
// 4 Deve retornar NULL se não conseguir ler o arquivo
// 5 Deve ler o arquivo apontado pelo FD com base no BUFFER_SIZE que poderá	ser fornecido
// 6 Deve processar a leitura do arquivo até	encontrar um '\n' ou EOF
// 7 A linha retornada deve incluir o '\n' se ele estiver presente, exceto se EOF foi alcançado e nao	há '\n'
// 9 Toda a memória alocada dinamicamente deve ser liberada
// 10 O uso de variável estática deve ser limitado em apenas uma
// 11 Toda leitura de ponteiro deve ser protegido contra segfault
// 12 A função deve trabalhar com 0, 1 ou N (ex 10000000) de	BUFFER_SIZE
// 13 A função deve lidar com leitura de FD em arquivo binário
// 14 A função deve ser capaz de ler múltiplos FDs
// 15 A função deve ser prototipada da seguinte maneira: char *get_next_line(int fd);
// 16 lseek, global variables are not allowed