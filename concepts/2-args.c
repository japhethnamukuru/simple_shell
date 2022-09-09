#include <stdio.h>

/**
 * main - prints command line args without usig ac
 *
 * Return: Always 0
 */

int main(int ac __attribute__((unused)), char **av)
{
	int i;

	for (i = 0; av[i]; i++)
		printf("av[%i]: %s\n", i, av[i]);
	return (0);
}
