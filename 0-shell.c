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
	static char buf[MAXARGS];

	while (getcmd(buf, sizeof(buf)) >= 0)
	{
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			buf[_strlen(buf) - 1] = 0;

			if (chdir(buf + 3) < 0)
				error("./shell");

			continue;
		}

		if (forkProcess() == 0)
			runcmd(parsecmd(buf));

		wait(NULL);
	}

	exit(0);
}
