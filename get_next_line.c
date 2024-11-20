# include "get_next_line.h"

char *get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;
	char		*temp;
	char		*line;
	int			index = 0;
	int			bytes_read = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return NULL;

	if (!backup)
		backup	= ft_strdup(EMPTY_STRING);

	while (!ft_strchr(backup, NEW_LINE))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(backup);
			backup = NULL;
			return (NULL);
		}
		else if (bytes_read	== 0)
			break;
		buffer[bytes_read] = NULL_CHAR;
		temp = backup;
		backup = ft_strjoin(backup, buffer);
		free(temp);
	}
	index = 0;
	if (backup[index] == NULL_CHAR)
	{
		free(buffer);
		free(backup);
		backup = NULL;
		return NULL;
	}

	while (backup[index] && backup[index] != NEW_LINE)
		index++;
	
	if (backup[index] && backup[index] == NEW_LINE)
		index++;
	line = ft_substr(backup, 0, index);
	if (!line)
	{
		free(backup);
		return NULL;
	}
	
	temp = backup;
	backup = ft_strdup(backup + index);
	free(temp);
	free(buffer);
	return line;
}
