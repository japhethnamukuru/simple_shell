#include "shell.h"

ssize_t mygetline(char **buff, size_t *n, FILE *stream)
{
	static size_t offset, len_input;
	static int counter;
	static ssize_t m;
	static char *input;
	size_t line_size, pos;
	int fd;

	line_size = 0;
	if (offset == 0)
	{
		fd = fileno(stream);
		input = malloc(sizeof(char) * 1024);
		m = read(fd, input, 1024);
	}

	if (m > 0)
	{
		if (input[m - 1] == '\n')
			input[m] = '\0';
		else
		{
			input[m] = '\n';
			input[m + 1] = '\0';
		}

		len_input = str_len(input);
		if (counter > 0)
			offset++;

		pos = offset;
		while (input[offset] != '\n')
		{
			line_size++;
			offset++;
		}
		if (*n <= line_size)
			*buff = malloc(sizeof(char) * (line_size + 2));

		if (*buff == NULL)
		{
			printf("Error: memory allocation failed");
			return (-1);
		}
		if (counter == 0)
			mem_cpy(*buff, input, line_size + 1);
		else
			mem_cpy(*buff, (input + pos), line_size + 1);

		mem_cpy((*buff + line_size + 1), "\0", 1);
	}

	if (offset + 1 == len_input || line_size == 0 || !(str_cmp(*buff, "exit\n")))
	{
		free(input);
		offset = 0;
	}
	else
		counter++;

	return (line_size + 1);
}
