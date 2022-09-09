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

	/* checking the size of pid_t using the sizeof operator */

	printf("The maximum size of a process is %lu\n", sizeof(pid_t));
	return (0);
}
