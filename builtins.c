#include "shell.h"

/**
  * check_builtin - checks a passed string if it's a builtin func
  * @builtin: the name to be checked
  * Return: the index of builtin if found, -1 otherwise
  */
int check_builtin(char *builtin)
{
	char *built_ins[] = {"exit", "env", "setenv", "unsetenv",
		"cd", "alias", "help", "history", NULL};
	int i;

	i = 0;
	while (built_ins[i])
	{
		if (str_cmp(builtin, built_ins[i]) == 0)
			return (i);

		i++;
	}

	return (-1);
}

/**
  * print_env - prints the environment
  * @args: the args vector
  * Description: uses the 'extern char **environ' global
  * variable. Handles the env builtin func
  * Return: always 0
  */
int print_env(char **args __attribute__((unused)))
{
	unsigned int i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}
/**
  * env_func - sets or unsets environment variables
  * @args: the arg vector
  * Return: 0 on success, 101 or 102 on error
  */
int env_func(char **args)
{
	int status, status2;

	status = status2 = 0;
	if (str_cmp(args[0], "setenv") == 0)
	{
		if (args[1] == NULL || args[2] == NULL)
		{
			printf("Usage: setenv VARIABLE VALUE\n");
			return (101);
		}

		if (getenv(args[1]) == NULL)
			status = setenv(args[1], args[2], 0);
		else
			status = setenv(args[1], args[2], 1);
	}
	else
	{
		if (args[1] == NULL)
		{
			printf("Usage: unsetenv VARIABLE\n");
			return (102);
		}

		status2 = unsetenv(args[1]);
	}

	if (status == -1)
	{
		perror("Error");
		return (101);
	}
	else if (status2 == -1)
	{
		perror("Error");
		return (102);
	}

	return (0);
}

/**
  * ch_dir - changes the cwd
  * @args: the arg vector
  * Return: 0 on success, 101 or 103 on failure
  */
int ch_dir(char **args)
{
	char *prwd, *home, *cwd = NULL;
	size_t size;
	int status, status2;

	size = 0;
	cwd = getcwd(cwd, size);
	home = getenv("HOME");
	prwd = getenv("OLDPWD");
	if (prwd == NULL)
		prwd = cwd;

	if (args[1])
	{
		if (str_cmp(args[1], "-") == 0)
		{
			status = setenv("PWD", prwd, 1);
			status = setenv("OLDPWD", cwd, 1);
			status2 = chdir(prwd);
		}
		else
		{
			status = setenv("PWD", args[1], 1);
			status = setenv("OLDPWD", cwd, 1);
			status2 = chdir(args[1]);
		}
	}
	else
	{
		status = setenv("PWD", home, 1);
		status = setenv("OLDPWD", cwd, 1);
		status2 = chdir(home);
	}
	
	free(cwd);
	if (status == -1)
	{
		perror("Error");
		return (101);
	}
	else if (status2 == -1)
	{
		perror("Error");
		return (103);
	}

	return (0);
}

/**
  * help - displays help texts for builtin commands
  * @args: the arg vector
  * Return: always 0
  */
int help(char **args)
{
	char exit_help[] = "exit: exit [n]\n\texits the shell with status n or status of last command if n is not given";
	char env_help[] = "env:\n\tprints all the environment variables. Returns nothing";
	char setenv[] = "setenv: setenv VAR VALUE\n\tset the env variable VAR to VALUE, overrides it, if it already exist. Returns success or 101";
	char unsetenv[] = "unsetenv: unsetenv VAR\n\tremove the env variable VAR if it exist. Returns success or 102";
	char cd_help[] = "cd: cd [DIR]\n\tchanges the cwd to DIR, if given, else changes it to $HOME. Returns success or 103";
	char alias_help[] = "alias: alias [name[='value']]\n\tprints all aliases if no arg was given or only aliases with names given.\n\tset alias for name to value or change the value to value if alias with\n\tname already exists. Return nothing";
	char *built_ins[] = {"exit", "env", "setenv", "unsetenv",
		"cd", "alias", NULL};
	char *help_texts[7];
	int i, j;

	if (args[1] == NULL || str_cmp(args[1], "help") == 0)
	{
		printf("help: help [command]\n\tThis is the help builtin command, supply a built-in command to display\n\tits help text.\n\tBuiltins: exit, cd, alias, env, setenv, unsetenv\n");
		return (0);
	}
	help_texts[0] = exit_help;
	help_texts[1] = env_help;
	help_texts[2] = setenv;
	help_texts[3] = unsetenv;
	help_texts[4] = cd_help;
	help_texts[5] = alias_help;
	help_texts[6] = NULL;
	i = 1;
	while (args[i])
	{
		j = 0;
		while (built_ins[j])
		{
			if (str_cmp(args[i], built_ins[j]) == 0)
			{
				printf("%s\n", help_texts[j]);
				break;
			}

			j++;
		}

		i++;
	}

	return (0);
}
