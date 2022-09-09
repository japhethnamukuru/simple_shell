#include "shell.h"

/**
  * logical_and - checks for the presence of && operator
  * @buff: the command input buffer
  * Description: if && is found, it splits the command and return
  * the first part to main to be run as a single command. if errno
  * is not 0, stops the execution for subsequent commands
  * Return: pointer to the next command, or NULL if none left
  */
char *logical_and(char *buff)
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
		curr_comm = strtok_r(buff_hold, "&&", &save_ptr);
	else
	{
		if (errno == 0)
			curr_comm = strtok_r(NULL, "&&", &save_ptr);
		else
			curr_comm = NULL;
	}

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
		if (strtok(curr_comm_cpy, " ") == NULL)
		{
			errno = 98;
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
  * logical_or - checks for the presence of || operator
  * @buff: the command input buffer
  * Description: if || is found, it splits the command and return
  * the first part to main to be run as a single command
  * Return: pointer to the next command, or NULL if none left
  */
char *logical_or(char *buff)
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
		curr_comm = strtok_r(buff_hold, "||", &save_ptr);
	else if (counter > 0 && errno == 0)
	{
		free(buff_hold);
		buff_hold = save_ptr = NULL;
		counter = 0;

		return (NULL);
	}
	else
		curr_comm = strtok_r(NULL, "||", &save_ptr);

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
		if (strtok(curr_comm_cpy, " ") == NULL)
		{
			errno = 99;
			free(curr_comm_cpy);
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

