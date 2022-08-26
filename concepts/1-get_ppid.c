#include <stdio.h>
#include <unistd.h>

/**
 * main - ppid
 *
 * Return: Always 0
 */

int main(void)
{
	pid_t my_ppid;

	my_ppid = getppid();

	printf("The parent process id is %u\n", my_ppid);
	return (0);
}
