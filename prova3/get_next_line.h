#define GET_NEXT_LINE_H
#ifdef GET_NEXT_LINE_H
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#define NULL_CHAR '\0'
#define BREAKLINE_CHAR '\n'
#define EMPTY_STRING ""

typedef struct s_gnl
{
	bool is_eof;
	char *content;
	int content_length;
	char *buffer;
	char *line;
}	t_gnl;

#endif