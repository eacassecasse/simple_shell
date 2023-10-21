#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * handleExec - Custom Function
 * @cmd: command to be executed
 *
 * Description: The logic behind the execution of a command
 */
void handleExec(struct cmd *cmd)
{
	struct execcmd *ecmd;

	ecmd = (struct execcmd *)cmd;

	if (ecmd->argv[0] == 0)
		exit(1);

	if (forkProcess() == 0)
	{
		close(STDOUT_FILENO);
		dup2(STDOUT_FILENO, 3);

		execve(ecmd->argv[0], ecmd->argv, NULL);

		error("execve command failed");
		exit(1);
	}

	wait(NULL);
}

/**
 * handleRedir - Custom Function
 * @cmd: command to be executed
 *
 * Description: The logic behind the I/O Redirection
 */
void handleRedir(struct cmd *cmd)
{
	struct redircmd *rcmd;

	rcmd = (struct redircmd *)cmd;

	close(rcmd->fd);

	if (open(rcmd->file, rcmd->mode) < 0)
	{
		error("Failed to open file\n");
		exit(1);
	}

	runcmd(rcmd->cmd);
}

/**
 * handleSeq - Custom Function
 * @cmd: command to be executed
 *
 * Description: The logic behind the Sequencing operation
 */
void handleSeq(struct cmd *cmd)
{
	struct listcmd *lcmd;

	lcmd = (struct listcmd *)cmd;

	if (forkProcess() == 0)
		runcmd(lcmd->left);

	wait(NULL);

	runcmd(lcmd->right);
}

/**
 * handlePipe - Custom Function
 * @cmd: command to be executed
 *
 * Description: The logic behind the Pipe operation
 */
void handlePipe(struct cmd *cmd)
{
	int p[2];
	struct pipecmd *pcmd;

	pcmd = (struct pipecmd *)cmd;

	if (pipe(p) < 0)
	{
		error("Failed to pipe command");
		exit(1);
	}

	if (forkProcess() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left);
	}

	if (forkProcess() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right);
	}

	close(p[0]);
	close(p[1]);
	wait(NULL);
	wait(NULL);
}
