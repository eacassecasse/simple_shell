#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * runcmd - Custom Function
 * @cmd: command to be executed
 *
 * Description: Executes a command
 */
void runcmd(struct cmd *cmd)
{
	if (cmd == 0)
		exit(1);

	switch (cmd->type)
	{
		case EXEC:
			handleExec(cmd);
			break;
		case REDIR:
			handleRedir(cmd);
			break;
		case LIST:
			handleSeq(cmd);
			break;
		case PIPE:
			handlePipe(cmd);
			break;
		default:
			error("Trying to exec a miscellaneous command");
			exit(1);
	}

	exit(0);
}

/**
 * getcmd - Custom Function
 * @buf: Buffer to insert user inputs
 * @nbuf: amount of bytes inside the buffer
 *
 * Description: Prints a $ and get user input
 *
 * Return: Integer
 */
int getcmd(char *buf, size_t nbuf)
{
	_puts("$ ");

	return (getline(&buf, &nbuf, stdin));
}

