#include "shell.h"
static char **ext_aliases;

/**
  * aliasing - entry point to the alias system, initializes the alias array
  * @args: the arg vector
  * Return: always 0
  */
int aliasing(char **args)
{
	static char **aliases;
	int i;

	if (aliases == NULL)
	{
		aliases = malloc(sizeof(char *) * 1);
		if (aliases)
			aliases[0] = NULL;
	}

	if (args)
	{
		i = 1;
		if (args[i])
		{
			while (args[i])
			{
				aliases = set_alias(args[i], aliases);
				i++;
			}
		}
		else
			aliases = set_alias(NULL, aliases);
	}

	ext_aliases = aliases;
	return (0);
}

/**
  * set_alias - determines whether to print, add or modify aliases
  * @arg: argument to the alias builtin
  * @aliases: the aliases array
  * Return: the aliases array, modified or not
  */
char **set_alias(char *arg, char **aliases)
{
	int i;
	char *alias, *arg_cpy, *value;

	if (arg == NULL)
	{
		i = 0;
		while (aliases[i])
		{
			printf("%s\n", aliases[i]);
			i++;
		}
	}
	else
	{
		arg_cpy = str_dup(arg);
		str_tok(arg_cpy, "=");
		value = str_tok(NULL, "=");
		alias = find_alias(arg, aliases);
		if (alias)
		{
			if (value)
				aliases = add_alias(arg, aliases, 1);
			else
				printf("%s\n", alias);
		}
		else
		{
			if (value)
				aliases = add_alias(arg, aliases, 0);
		}

		free(arg_cpy);
	}

	return (aliases);
}

/**
  * find_alias - finds and return an alias in the array, if it exist
  * @alias: the alias to find
  * @aliases: the aliases array
  * Return: the alias, if found, NULL otherwise
  */
char *find_alias(char *alias, char **aliases)
{
	char *alias_cpy, *alias_cpy2, *name, *name2, *save_ptr;
	int i;

	i = 0;
	save_ptr = NULL;
	while (aliases[i])
	{
		alias_cpy = str_dup(alias);
		alias_cpy2 = str_dup(aliases[i]);
		name = str_tok_r(alias_cpy, "=", &save_ptr);
		name2 = str_tok_r(alias_cpy2, "=", &save_ptr);
		if (str_cmp(name, name2) == 0)
		{
			free(alias_cpy);
			free(alias_cpy2);
			return (aliases[i]);
		}

		free(alias_cpy);
		free(alias_cpy2);
		i++;
	}

	return (NULL);
}

/**
  * add_alias - adds or modify an existing alias
  * @alias: the alias to add or modify
  * @aliases: the aliases array
  * @overwrite: 0 to add a new, 1 to overwrite an existing one
  * Return: the modified aliases array
  */
char **add_alias(char *alias, char **aliases, int overwrite)
{
	char *alias_cpy, *alias_cpy2, *name, *name2;
	size_t len, i;

	i = 0;
	len = len_array(aliases);
	if (overwrite == 1)
	{
		for (i = 0; i < len; i++)
		{
			alias_cpy = str_dup(alias);
			alias_cpy2 = str_dup(aliases[i]);
			name = str_tok(alias_cpy, "=");
			name2 = str_tok(alias_cpy2, "=");
			if (str_cmp(name, name2) == 0)
			{
				free(aliases[i]);
				free(alias_cpy);
				free(alias_cpy2);
				aliases[i] = str_dup(alias);
				break;
			}
			free(alias_cpy);
			free(alias_cpy2);
		}
	}
	else
	{
		aliases = realloc(aliases, sizeof(char *) * (len + 2));
		if (aliases)
		{
			aliases[len] = str_dup(alias);
			aliases[len + 1] = NULL;
		}
	}

	return (aliases);
}

/**
  * get_aliases - returns the aliases array
  * none
  * Description: this is a function to access the global
  * aliases array from elsewhere in the program
  * Return: the global aliases array
  */
char **get_aliases(void)
{
	return (ext_aliases);
}
