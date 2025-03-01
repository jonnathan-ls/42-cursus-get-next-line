
#define GET_NEXT_LINE_H
#ifdef GET_NEXT_LINE_H
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

typedef struct  s_gnl
{
	bool is_eof;
	char *content;
	long size_content;
} t_gnl;

#endif