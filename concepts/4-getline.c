#include <stdio.h>
#include <stdlib.h>

/**
 * main - getline()
 *
 * Return: Always 0
 */

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Please specify a file.");
		exit(EXIT_FAILURE);
	}

	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	stream = fopen(argv[1], "r");
	if (stream == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, stream) != -1))
	{
		printf("Retreaved line of length %zu :\n", read);
		printf("%s", line);
	}

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}
