#include "shell.h"

/**
  * execute - executes a program in a child process with the arguments passed
  * @args: the argument vector
  * @env: the environment to pass to the program
  * Return: 0 if success, -1 otherwise
  */
int execute(char **args, char **env)
{
	pid_t child;
	int status;
	struct stat st;

	if (stat(args[0], &st) == -1)
		return (-1);

	child = fork();
	if (child == -1)
	{
		return (-1);
	}

	if (child == 0)
	{
		if (execve(args[0], args, env) == -1)
			_exit(-1);
	}
	else
	{
		if (waitpid(child, &status, 0) == -1)
			return (-1);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
	}

	return (0);
}

/**
  * exec_builtin - execute a given builtin function
  * @index: index of the function
  * @args: the arg vector
  * Return: nothing
  */
void exec_builtin(int index, char **args)
{
	int (*builtin_ptrs[])(char **) = {print_env,
		env_func, env_func, ch_dir, aliasing, help, display_history};

	if (index == 0)
		free_args_exit(args);
	else
		errno = builtin_ptrs[index - 1](args);
}
