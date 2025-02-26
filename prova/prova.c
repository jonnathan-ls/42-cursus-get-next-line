
#include "get_next_line.h"
#include <stdbool.h>
#include <stdio.h>


int main(void)
{
	int fd = open("./content", 'r');
	printf("Valor: %s", get_next_line(fd));
	close(fd);
}