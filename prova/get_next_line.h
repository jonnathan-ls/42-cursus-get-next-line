#ifndef PROVA_H
# define PROVA_H
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 11
#endif

# define NEW_LINE '\n'
# define NULL_CHAR '\0'
# define EMPTY_STRING ""

char	*get_next_line(int fd);

#endif
