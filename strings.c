#include "shell.h"

/**
  * str_cmp - compares two strings
  * @s1: first string
  * @s2: second string
  * Return: neg, 0, or pos int if s1 is less than, matches or greater than s2
  */
int str_cmp(char *s1, char *s2)
{
	size_t i, j;
	int res;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = j = 0;
	do {
		if (s1[i] == s2[j])
		{
			res = 0;
			j++;
		}
		else
		{
			res = s1[i] - s2[j];
			break;
		}
	} while (s1[++i]);

	return (res);
}

/**
  * mem_cpy - copies a given number of char from src to dest
  * @dest: destination
  * @src: source
  * @n: number of chars to copy
  * Return: dest or NULL if dest or src is NULL
  */
char *mem_cpy(char *dest, const char *src, size_t n)
{
	size_t i;

	if (dest == NULL || src == NULL)
		return (NULL);

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (dest);
}

/**
  * str_ncmp - compares the first n bytes of two strings
  * @s1: first string
  * @s2: second string
  * @n: numbers of char to compare
  * Return: neg, 0, or pos int if s1 is less than, matches or greater than s2
  */
int str_ncmp(char *s1, char *s2, size_t n)
{
	size_t i, j;
	int res;

	i = j = 0;
	do{
		if (s1[i] == s2[j])
		{
			res = 0;
			j++;
		}
		else
		{
			res = s1[i] - s2[j];
			break;
		}
	} while (++i < n && s1[i]);

	return (res);
}

/**
  * str_dup - duplicates a string
  * @s: the string
  * Return: pointer to the duplicate or NULL if s is NULL
  */
char *str_dup(char *s)
{
	char *dup;

	if (s == NULL)
		return (NULL);

	dup = malloc(sizeof(char) * (str_len(s) + 1));
	mem_cpy(dup, s, str_len(s) + 1);

	return (dup);
}

/**
  * str_len - finds the length of a string
  * @s: the string
  * Return: length of s, -1 if s is NULL
  */
size_t str_len(char *s)
{
	if (s == NULL)
		return (-1);
	if (*s == '\0')
		return (0);

	return (str_len(s + 1) + 1);
}
