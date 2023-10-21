#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


/**
 * parsepipe - Custom Function
 * @ps: pointer to the string
 * @es: pointer to somewhere in the buffer
 *
 * Description: Parses a buffer containing shell
 *		commands to find pipes
 * Return: An command structure
 */
struct cmd *parsepipe(char **ps, char *es)
{
	struct cmd *cmd;

	cmd = parseexec(ps, es);

	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}

	return (cmd);
}

/**
 * parseline - Custom Function
 * @ps: pointer to the string
 * @es: pointer to somewhere in the buffer
 *
 * Description: Parses a buffer containing shell
 *		commands to find sequences and/or
 *		background operations
 * Return: An command structure
 */
struct cmd *parseline(char **ps, char *es)
{
	struct cmd *cmd;

	cmd = parsepipe(ps, es);

	if (peek(ps, es, ";"))
	{
		gettoken(ps, es, 0, 0);
		cmd = listcmd(cmd, parseline(ps, es));
	}

	return (cmd);
}

/**
 * parseblock - Custom Function
 * @ps: pointer to the string
 * @es: pointer to somewhere in the buffer
 *
 * Description: Parses a buffer containing shell
 *		commands to find blocks (operations
 *		inside parentheses)
 * Return: An command structure
 */
struct cmd *parseblock(char **ps, char *es)
{
	struct cmd *cmd;

	cmd = parsepipe(ps, es);

	if (!peek(ps, es, "("))
	{
		error("Failed to find block");
		exit(1);
	}

	gettoken(ps, es, 0, 0);
	cmd = parseline(ps, es);

	if (!peek(ps, es, ")"))
	{
		error("Syntax error - Missing )");
		exit(1);
	}

	gettoken(ps, es, 0, 0);
	cmd = parseredirs(cmd, ps, es);

	return (cmd);
}

/**
 * parseredirs - Custom Function
 * @cmd: A command to redir
 * @ps: pointer to the string
 * @es: pointer to somewhere in the buffer
 *
 * Description: Parses a buffer containing shell
 *		commands to find blocks (operations
 *		inside parentheses)
 * Return: An command structure
 */
struct cmd *parseredirs(struct cmd *cmd, char **ps, char *es)
{
	int tok;
	char *q, *eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);

		if (gettoken(ps, es, &q, &eq) != 'a')
		{
			error("./shell");
			exit(1);
		}

		switch (tok)
		{
			case '<':
				cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
				break;
			case '>':
				cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1);
				break;
			case '+':
				cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT, 1);
				break;
		}
	}

	return (cmd);
}

/**
 * parseexec - Custom Function
 * @ps: pointer to the string
 * @es: pointer to somewhere in the buffer
 *
 * Description: Parses a buffer containing shell
 *		commands to find executable
 *		command
 * Return: An command structure
 */
struct cmd *parseexec(char **ps, char *es)
{
	struct cmd *ret;
	struct execcmd *cmd;
	char *q, *eq;
	int tok, argc;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));

	ret = execcmd();
	cmd = (struct execcmd *)ret;

	argc = 0, ret = parseredirs(ret, ps, es);

	while (!peek(ps, es, "|);"))
	{
		tok = gettoken(ps, es, &q, &eq);

		if (tok == 0)
			break;

		if (tok != 'a')
		{
			error("Syntax error");
			exit(1);
		}

		cmd->argv[argc] = q, cmd->eargv[argc] = eq, argc++;

		/*if (argc >= MAXARGS)
		{
			error("./shell");
			exit(1);
		}*/

		ret = parseredirs(ret, ps, es);
	}

	cmd->argv[argc] = 0, cmd->eargv[argc] = 0;

	return (ret);
}

