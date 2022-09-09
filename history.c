#include "shell.h"
static char **history;

/**
  * read_history - reads from the history file and save to an array
  * none
  * Return: 0 on success, -1 otherwise
  */
int read_history(void)
{
	FILE *history_file;
	size_t n, len;
	char *path, *home, *line, **hist;

	hist = malloc(sizeof(char *));
	hist[0] = NULL;
	home = getenv("HOME");
	path = malloc(sizeof(char) * (str_len(home) + 23));
	if (path)
	{
		mem_cpy(path, home, str_len(home));
		mem_cpy(path + str_len(home), "/.simple_shell_history", 23);
		history_file = fopen(path, "r");
		if (history_file == NULL)
		{
			free(path);
			return (-1);
		}
		n =  0;
		line = NULL;
		while (getline(&line, &n, history_file) > 0)
		{
			len = len_array(hist);
			hist = realloc(hist, sizeof(char *) * (len + 2));
			hist[len] = str_dup(line);
			hist[len + 1] = NULL;
		}

		fclose(history_file);
		free(path);
		free(line);
	}

	history = hist;
	return (0);
}

/**
  * display_history - displays the shell history
  * @args: the arg vector
  * Return: 0 on success, -1 otherwise
  */
int display_history(char **args __attribute__((unused)))
{
	size_t i;

	i =  0;
	while (history[i])
	{
		printf("%lu %s", i, history[i]);
		i++;
	}

	return (0);
}

/**
  * add_to_history - adds a new command to the history array
  * @command: the command entered
  * Return: 0 on success, -1 otherwise
  */
int add_to_history(char *command)
{
	char *comm;
	unsigned int len_command;
	size_t len;

	if (command)
	{
		len_command = str_len(command);
		comm = malloc(sizeof(char) * (len_command + 2));
		if (comm)
		{
			mem_cpy(comm, command, len_command);
			mem_cpy(comm + len_command, "\n", 1);
			mem_cpy(comm + len_command + 1, "\0", 1);
			len = len_array(history);
			history = realloc(history, sizeof(char *) * (len + 2));
			if (history == NULL)
			{
				free(comm);
				return (-1);
			}
			history[len] = comm;
			history[len + 1] = NULL;
		}
		else
			return (-1);
	}

	return (0);
}

/**
  * write_history - writes the history array to a file in $HOME
  * none
  * Return: 0 on success, -1 otherwise
  */
int write_history(void)
{
	int fd, i;
	char *path, *home;

	home = getenv("HOME");
	path = malloc(sizeof(char) * (str_len(home) + 23));
	if (path)
	{
		mem_cpy(path, home, str_len(home));
		mem_cpy(path + str_len(home), "/.simple_shell_history", 23);
		fd = open(path, O_WRONLY | O_CREAT, 0666);
		if (fd == -1)
		{
			free(path);
			return (-1);
		}

		i = 0;
		while (history[i])
		{
			write(fd, history[i], str_len(history[i]));
			i++;
		}

		close(fd);
		free(path);
	}

	return (0);
}

/**
  * get_history - return the history array outside this file
  * none
  * Return: pointer to the history array
  */
char **get_history(void)
{
	return (history);
}
