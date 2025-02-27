
#include "get_next_line.h"
#include <stdbool.h>
#include <stdio.h>


int main(void)
{
	int fd = open("./content", 'r');
	while (true)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	close(fd);
}