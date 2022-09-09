#include "shell.h"

/**
  * parse_command - creates an null terminated array of words from a string
  * @comm: the command string
  * @delim: the delimiter
  * Description: uses space character as the delimiter and splits the
  * command string into words, saving the pointer to each word into
  * a malloc'ed array
  * Return: pointer to the array/arg vector
  */
char **parse_command(char *comm, char *delim)
{
	char **args, *comm_cpy, *path, *path_cpy;
	unsigned int n_words, i;

	if (comm == NULL)
		return (NULL);

	comm_cpy = str_dup(comm);
	n_words = 0;
	if (str_tok(comm_cpy, delim))
		n_words++;
	while (str_tok(NULL, delim))
		n_words++;

	args = malloc(sizeof(char *) * (n_words + 1));
	if (args == NULL)
	{
		printf("Unable to allocate memory\n");
		return (NULL);
	}

	path = str_tok(comm, delim);
	path_cpy = get_alias(str_dup(path));
	if (check_builtin(path_cpy) != -1)
		args[0] = path_cpy;
	else
	{
		args[0] = get_full_path(path_cpy);
		free(path_cpy);
	}

	for (i = 1; i < n_words; i++)
	{
		path = str_tok(NULL, delim);
		args[i] = str_dup(path);
	}

	args[i] = NULL;
	free(comm_cpy);

	return (args);
}
