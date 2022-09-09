#include <stdio.h>
#include <stdlib.h>

/**
 * main - getline from stdin and print it
 *
 * Return: Always 0
 */

int main(void)
{
	printf("$ ");

	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;

	read = getline(&line, &len, stdin);
	printf("%s\n", line);

	free(line);

	return (0);
}
