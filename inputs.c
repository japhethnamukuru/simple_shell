#include "shell.h"

/**
  * get_input - gets the user input command and save it in buff
  * @buff: the buffer
  * @av: the arg vector
  * @env: the environment list
  * Return: number of character entered
  */
ssize_t get_input(char **buff, char **av, char **env)
{
	size_t n;
	ssize_t m;
	char *buff_cpy;

	n = 0;
	m = mygetline(buff, &n, stdin);

	/* if the input is piped or EOF, the next iteration, m is 0 */
	if (m < 1)
	{
		free(*buff);
		/*if input is from the terminal, restart*/
		if (isatty(STDIN_FILENO))
			execve(av[0], av, env);
		/*if it's piped, exit*/
		exit(errno);
	}
	/**
	  * this is to handle EOF when ctrl-D is pressed
	  * after input since there'll be no newline
	 */
	if (m > 1 && *(*buff + m - 1) != '\n')
		*(*buff + m) =  '\0';
	else
	/*this overrides the newline at the end from getline()*/
		*(*buff + m - 1) = '\0';
	/*this restart if only spaces are entered*/
	buff_cpy = str_dup(*buff);
	if (str_tok(buff_cpy, " ") == NULL)
	{
		free(buff_cpy);
		free(*buff);
		execve(av[0], av, env);
	}
	else
		free(buff_cpy);

	return (m);
}

/**
  * check_separator - checks for the presence of the command separator (;)
  * @buff: the input buffer containing the command string
  * Description: uses a static buffer to hold the initial command string
  * and then search for ; and uses strtok to return the next command.
  * finally returns NULL if there are no ; left
  * Return: pointer to the next command or NULL
  */
char *check_separator(char *buff)
{
	static char *buff_hold, *save_ptr;
	static int counter;
	char *curr_comm, *curr_comm_cpy, *curr_comm_cpy2;

	if (buff != NULL && buff_hold == NULL)
	{
		buff_hold = str_dup(buff);
		free(buff);
	}

	if (buff_hold == NULL)
		return (NULL);

	if (counter == 0)
		curr_comm = strtok_r(buff_hold, ";", &save_ptr);
	else
		curr_comm = strtok_r(NULL, ";", &save_ptr);

	counter++;
	if (curr_comm == NULL)
	{
		free(buff_hold);
		buff_hold = save_ptr = NULL;
		counter = 0;

		return (NULL);
	}
	else
	{
		curr_comm_cpy = str_dup(curr_comm);
		curr_comm_cpy2 = str_dup(curr_comm);
		if (str_tok(curr_comm_cpy, " ") == NULL)
		{
			errno = 100;
			free(curr_comm_cpy);
			free(curr_comm_cpy2);
			free(buff_hold);
			buff_hold = save_ptr = NULL;
			counter = 0;

			return (NULL);
		}
		if (str_cmp(strtok(curr_comm_cpy, " "), "exit") == 0)
			free(buff_hold);

		free(curr_comm_cpy);

		return (curr_comm_cpy2);
	}
}

/**
  * expand_vars - function for variable replacements
  * @args: the arg vector
  * Return: nothing
  */
void expand_vars(char **args)
{
	size_t i, j;
	char *var;

	i = 1;
	while (args[i])
	{
		if (*(args[i]) == '$')
		{
			if (str_cmp(args[i], "$?") == 0)
			{
				free(args[i]);
				args[i] = int_to_str(errno);
			}
			else if (str_cmp(args[i], "$$") == 0)
			{
				free(args[i]);
				args[i] = int_to_str(getpid());
			}
			else
			{
				var = str_dup(getenv(args[i] + 1));
				free(args[i]);
				if (var)
					args[i] = var;
				else
				{
					for (j = i; j < len_array(args); j++)
						args[j] = args[j + 1];
				}

			}
		}

		i++;
	}
}
/**
  * free_args - frees the arg vector created by 'parse_command'
  * @args: the arg vector generated from user input
  * Return: nothing
  */
void free_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}

	free(args);
}

/**
  * free_args_exit - frees the arg vector and exit the shell
  * @args: the args vector
  * Return: nothing
  */
void free_args_exit(char **args)
{
	int status;

	if (args[1])
		status = _atoi(args[1]);
	else
		status = errno;

	free_args(args);
	free_args(get_aliases());
	if (write_history() == -1)
		perror("Unable to write history");

	free_args(get_history());

	exit(status);
}
