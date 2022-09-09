#include "shell.h"

/**
  * main - a simple shell interpreter
  * @ac: arg count
  * @av: arg vector
  * @env: the evironment
  * Return: never returns until a kill signal is sent
  */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	char **args, *buff;
	ssize_t flag;
	int index;

	signal(SIGINT, sigint_handler);

	if (av[1])
	{
		file_mode(av, env);
	}

	read_history();
	aliasing(NULL);
	flag = 1;
	while (flag > 0)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "my_shell$ ", 10);

		buff = NULL;
		flag = get_input(&buff, av, env);
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
	}

	return (0);
}

/**
  * sigint_handler - restarts the program on ctrl-c
  * @sig: the signal number
  * Return: nothing
  */
void sigint_handler(int sig)
{
	if (sig == 2)
	{
		write(STDOUT_FILENO, "\nmy_shell$ ", 11);
		return;
	}
}
