#include "shell.h"

/**
  * file_mode - handles the shell file mode
  * @av: the arg vector
  * @env: the environment list
  * Return: nothing
  */
void file_mode(char **av, char **env)
{
	char *line;
	size_t n;
	ssize_t m;
	FILE *file;

	file = fopen(av[1], "r");
	if (file == NULL)
	{
		perror(av[0]);
		exit(errno);
	}

	line = NULL;
	n = 0;
	read_history();
	aliasing(NULL);
	while ((m = mygetline(&line, &n, file)) > 0)
	{
		line[str_len(line) - 1] = '\0';
		if (str_cmp(line, "exit") == 0)
			fclose(file);
		run_command(av, env, line);
		line = NULL;
	}

	free(line);
	fclose(file);
	free_args(get_aliases());
	free_args(get_history());
	exit(errno);
}

/**
  * run_command - runs each command per line
  * @av: the arg vector
  * @env: environment list
  * @buff: the command read on the line
  * Return: nothing
  */
void run_command(char **av, char **env, char *buff)
{
	char **args;
	int index;

	if (add_to_history(buff) == -1)
		perror(av[0]);
	comments(buff);
	while ((buff = check_separator(buff)))
	{
		while ((buff = logical_and(buff)))
		{
			while ((buff = logical_or(buff)))
			{
				args = NULL;
				args = parse_command(buff, " ");
				free(buff);

				expand_vars(args);
				index = check_builtin(args[0]);
				if (index != -1)
					exec_builtin(index, args);
				else
					if (execute(args, env) == -1)
						perror(av[0]);
				free_args(args);
			}
		}
	}
	if (errno == 98)
		printf("%s: syntax error, unexpected token '&&' \n", av[0]);
	else if (errno == 99)
		printf("%s: syntax error, unexpected token '||' \n", av[0]);
}
