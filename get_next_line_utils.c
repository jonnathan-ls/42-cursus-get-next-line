/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:28 by jlacerda          #+#    #+#             */
/*   Updated: 2024/11/16 22:11:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
