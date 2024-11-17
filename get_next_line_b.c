/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:04 by jlacerda          #+#    #+#             */
/*   Updated: 2024/11/18 17:52:04 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include	"get_next_line.h"

# include <unistd.h>
# include	<stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

char	*ft_strdup(const char *src)
{
	int		src_size;
	char	*str_cpy;

	src_size = ft_strlen(src);
	str_cpy = (char *)malloc(src_size + 1);
	if (str_cpy != NULL)
	{
		ft_strlcpy(str_cpy, src, src_size + 1);
	}
	return (str_cpy);
}


char	*ft_strjoin(char const *s1, char const *s2, int *eol)
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
			*eol = s2[i - s1_size] == '\n';
			joined_str[i] = s2[i - s1_size];
			i++;
		}
		joined_str[i] = '\0';
	}
	return (joined_str);
}

static void	ft_add_buffer_to_line(int *index, char *buffer, char *line, int *eol)
{
	int			buffer_index;

	buffer_index = 0;
	if (!buffer || !line)
		return ;
	while (*buffer && buffer[buffer_index] && !*eol)
	{
		*eol = buffer[buffer_index] == '\n';
		line[*index] = buffer[buffer_index];
		buffer_index++;
		(*index)++;
	}
}

static char	*ft_extract_line(char *buffer, char *line, int fd)
{
	static int	line_index;
	int			bytes_read;
	int			end_of_line;
	int			end_of_file;

	line_index = 0;
	end_of_line = 0;
	end_of_file = 0;
	line	= ft_strdup("");
	while (!end_of_line && !end_of_file)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			line = NULL;
			break ;
		}
		line = ft_strjoin(line, buffer, &end_of_line);
		if (!end_of_line)
		end_of_file = bytes_read == 0;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		buffer[BUFFER_SIZE];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	line = ft_extract_line(buffer, line, fd);
	return (line);
}

// #include <stdio.h>
// int main()
// {
// 	int fd;
// 	fd = open("text.txt", 'r');
// 	char *r = get_next_line(fd);
// 	printf("%s", r);
// 	return (0);
// } 


// 1 A função vai receber um FD 
// Deve ler o arquivo apontado pelo FD com base no BUFFER_SIZE que poderá	ser fornecido
// Deve retornar NULL se o FD ou BUFFER_SIZE for menor ou igual a 0

	// return value

// 	Read line: correct behavior
// NULL: there is nothing else to read, or an error
// occurred

// line return should include \n
	// exceção se o arquivo terminar ou nao terminar com \n

// • Chamadas repetidas (por exemplo, usando um loop) para sua função get_next_line() devem permitir
// que você leia o arquivo de texto apontado pelo descritor de arquivo, uma linha de cada vez.
// • Sua função deve retornar a linha que foi lida.
// Se não houver mais nada para ler ou se ocorrer um erro, ela deve retornar NULL.
// • Certifique-se de que sua função funcione conforme o esperado ao ler um arquivo e ao
// ler da entrada padrão.
// • Observe que a linha retornada deve incluir o caractere \n de terminação,
// exceto se o fim do arquivo foi alcançado e não termina com um caractere \n.
// • Seu arquivo de cabeçalho get_next_line.h deve conter pelo menos o protótipo da
// função get_next_line().
// • Adicione todas as funções auxiliares de que você precisa no arquivo get_next_line_utils.c.
// Um bom começo seria saber o que é uma variável estática.
// 5
// Obter próxima linha Ler uma linha de um fd é muito tedioso
// • Como você terá que ler arquivos em get_next_line(), adicione esta opção à sua
// chamada do compilador: -D BUFFER_SIZE=n
// Ela definirá o tamanho do buffer para read().
// O valor do tamanho do buffer será modificado pelos seus avaliadores de pares e pelo Moulinette
// para testar seu código.
// Devemos ser capazes de compilar este projeto com e sem o sinalizador -D
// BUFFER_SIZE além dos sinalizadores usuais. Você pode escolher o
// valor padrão de sua escolha.
// • Você compilará seu código da seguinte forma (um tamanho de buffer de 42 é usado como exemplo):
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
// • Consideramos que get_next_line() tem um comportamento indefinido se o arquivo apontado
// pelo descritor de arquivo mudou desde a última chamada, enquanto read() não atingiu o
// fim do arquivo.
// • Também consideramos que get_next_line() tem um comportamento indefinido ao ler
// um arquivo binário. No entanto, você pode implementar uma maneira lógica de lidar com esse comportamento se
// quiser.

// Sua função ainda funciona se o valor BUFFER_SIZE for 9999? Se
// for 1? 10000000? Você sabe por quê?
// Tente ler o mínimo possível cada vez que get_next_line() for
// chamado. Se você encontrar uma nova linha, você tem que retornar a linha
// atual.
// Não leia o arquivo inteiro e então processe cada linha.