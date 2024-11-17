/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:40 by jlacerda          #+#    #+#             */
/*   Updated: 2024/11/16 22:18:19 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include	<stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif


size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2, int *eol);

char	*get_next_line(int fd);

#endif
