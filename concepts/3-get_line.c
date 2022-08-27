#include <stdio.h>
#include <stdlib.h>

/**
 * main - getline
 *
 * Return: Always 0;
 */

int main(void)
{
	printf("type something:\n");

	char *line = NULL;
	size_t len = 0;
	ssize_t lineSize = 0;

	lineSize = getline(&line, &len, stdin);

	printf("You typed %swhich has %zu chars.\n", line, lineSize - 1);
	free(line);

	return (0);
}
