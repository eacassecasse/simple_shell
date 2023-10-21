#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * error - Entry Point
 * @msg: The message to be printed
 *
 * Description: Prints an error message
 */
void error(const char *msg)
{
	perror(msg);
}

/**
 * forkProcess - Entry Point
 *
 * Description: Creates a process using fork
 *
 * Return: The PID of the new created process
 */
int forkProcess(void)
{
	int pid;

	pid = fork();

	if (pid == -1)
	{
		error("It was unable to fork a child process");
		exit(1);
	}

	return (pid);
}

