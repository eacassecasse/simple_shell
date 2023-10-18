#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * main - Entry Point
 *
 * Description: Evaluates if the command passed exists
 * Return: 0 - Always Success
 */
int main(void)
{

	pid_t pid = forkProcess();

	if (pid == 0)
	{
		int exitFlag = 0;

		do {
			_puts("$ ");

			char *in = NULL;

			readIn(&in);

			char **args = parseLine(in);

			if (_strcmp(args[0], "exit") == 0)
				exit(0);

			runCmd(args[0], args);

			free(in);

		} while (exitFlag == 0);
	}

	wait(NULL);

	return (0);
}
