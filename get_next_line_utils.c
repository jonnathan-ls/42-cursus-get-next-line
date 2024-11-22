/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:28 by jlacerda          #+#    #+#             */
/*   Updated: 2024/11/21 22:58:49 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *src)
{
	int		src_size;
	char	*str_cpy;
	int		index;

	src_size = ft_strlen(src);
	str_cpy = (char *)malloc(src_size + 1);
	index = 0;
	while (src[index])
	{
		str_cpy[index] = src[index];
		index++;
	}
	str_cpy[index] = '\0';
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
	size_t	index;
	size_t	s_len;
	size_t	substr_len;
	char	*substr;

	index = 0;
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
		while (index < len && start + index < s_len)
		{
			substr[index] = s[start + index];
			index++;
		}
		substr[index] = '\0';
	}
	return (substr);
}

char	*ft_strjoin(const char *s1, const char *s2)
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
