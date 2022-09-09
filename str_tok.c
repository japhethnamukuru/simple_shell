#include "shell.h"

/**
  * str_tok - breaks a string into tokens using a delimiter specified
  * @str: the string
  * @delim: the delimeter
  * Description: splits up a string by putting '\0' where a delimiter
  * character is found and returning the pointer to the start of the
  * word that was found. Works exactly like the standard lib strtok
  * Return: pointer to the next token/word
  */
char *str_tok(char *str, char *delim)
{
	static char *pos;
	char *word;
	size_t len_delim, i;

	if ((str == NULL || *str == 0) && pos == NULL)
		return (NULL);
	else if (str == NULL && pos != NULL)
		str = pos;
	else if (str != NULL && pos != NULL)
		pos = NULL;

	if (delim == NULL || *delim == 0)
		return (str);

	len_delim = str_len(delim);
	while (*str == *delim && *str != 0)
	{
		if (str_ncmp(str, delim, len_delim) == 0)
		{
			str += len_delim;
			pos = str;
		}
		else
			break;
	}

	i = 0;
	word = str;
	while (*(str + i) != *delim && *(str + i) != 0)
	{
		i++;
		if (*(str + i) == *delim)
		{
			if (str_ncmp(str + i, delim, len_delim) == 0)
			{
				*(str + i) = '\0';
				str += len_delim + i;
				pos = str;
				break;
			}
			else
				str++;
		}
		else if (*(str + i) == 0)
		{
			pos = NULL;
			break;
		}
	}

	if (*word == 0)
		return (NULL);
	else
		return (word);
}

/**
  * str_tok_r - re-entrant version of str_tok
  * @str: the string
  * @delim: the delimeter
  * @save_ptr: the pointer to the location of the next token
  * Description: splits up a string by putting '\0' where a delimiter
  * character is found and returning the pointer to the start of the
  * word that was found. Works exactly like the standard lib strtok_r
  * Return: pointer to the next token/word
  */
char *str_tok_r(char *str, char *delim, char **save_ptr)
{
	char *word;
	size_t len_delim, i;

	if ((str == NULL || *str == 0) && *save_ptr == NULL)
		return (NULL);
	else if (str == NULL && *save_ptr != NULL)
		str = *save_ptr;
	else if (str != NULL && *save_ptr != NULL)
		*save_ptr = NULL;

	if (delim == NULL || *delim == 0)
		return (str);

	len_delim = str_len(delim);
	while (*str == *delim && *str != 0)
	{
		if (str_ncmp(str, delim, len_delim) == 0)
		{
			str += len_delim;
			*save_ptr = str;
		}
		else
			break;
	}

	i = 0;
	word = str;
	while (*(str + i) != *delim && *(str + i) != 0)
	{
		i++;
		if (*(str + i) == *delim)
		{
			if (str_ncmp(str + i, delim, len_delim) == 0)
			{
				*(str + i) = '\0';
				str += len_delim + i;
				*save_ptr = str;
				break;
			}
			else
				str++;
		}
		else if (*(str + i) == 0)
		{
			*save_ptr = str + i;
			break;
		}
	}

	if (*word == 0)
		return (NULL);
	else
		return (word);
}
