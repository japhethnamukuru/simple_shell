#include "shell.h"

/**
  * len_array - computes the length of an array of strings
  * @array: null terminated string array
  * Return: length of the array
  */
size_t len_array(char **array)
{
	size_t len;

	len = 0;
	while (array[len])
	{
		len++;
	}

	return (len);
}

/**
  * get_alias - finds and return the value of an alias if one exists
  * @name: the alias
  * Return: the value of the alias, if found or NULL otherwise
  */
char *get_alias(char *name)
{
	char *value, *value2, *alias, *alias_h, *alias_cpy, *next_name, *save_ptr;

	save_ptr = NULL;
	alias = find_alias(name, get_aliases());
	alias_h = alias;
	while (alias)
	{
		alias_h = alias;

		alias_cpy = str_dup(alias);
		str_tok_r(alias_cpy, "=", &save_ptr);
		value = str_dup(str_tok_r(NULL, "=", &save_ptr));
		next_name = str_dup(str_tok_r(value, "'", &save_ptr));
		alias = find_alias(next_name, get_aliases());
		free(next_name);
		free(value);
		free(alias_cpy);
	}

	if (alias_h)
	{
		alias_cpy = str_dup(alias_h);
		str_tok_r(alias_cpy, "=", &save_ptr);
		value = str_dup(str_tok_r(NULL, "=", &save_ptr));
		value2 = str_dup(str_tok_r(value, "'", &save_ptr));
		free(value);
		free(alias_cpy);
		free(name);

		return (value2);
	}
	else
		return (name);
}

/**
  * int_to_str - converts and integer to string
  * @num: the number
  * Return: pointer to the string
  */
char *int_to_str(size_t num)
{
	char *str;
	size_t num_hold;
	int i, len;

	num_hold = num;
	len = 1;

	while (num_hold / 10)
	{
		num_hold = num_hold / 10;
		len++;
	}

	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
	{
		printf("Unable to malloc memory");
		return (NULL);
	}

	for (i = len - 1; i >= 0; i--)
	{
		str[i] = (num % 10) + '0';
		num = num / 10;
	}
	str[len] = '\0';

	return (str);
}

/**
 * _atoi - converts a given string to an integer
 * @s: the string to be converted
 * Return: int value of the string, 0 if there's no numbers in s
 */
int _atoi(char *s)
{
	int sign;
	unsigned int num;

	num = 0;
	sign = 1;
	while (*s != 0)
	{
		if (*s == '-')
			sign *= -1;
		else if (*s >= '0' && *s <= '9')
			num = (num * 10) + *s % 48;
		else if (num > 0)
			break;
		s++;
	}

	return (num * sign);
}

/**
  * comments - handles the comment character #
  * @buff: the input buffer
  * Return: nothing
  */
void comments(char *buff)
{
	int i, j;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == ' ' && buff[i + 1] == '#')
		{
			j = 0;
			while (buff[i + j])
			{
				buff[i + j] = '\0';
				j++;
			}
		}

		i++;
	}
}
