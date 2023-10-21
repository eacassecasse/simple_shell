#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * parsecmd - Custom Function
 * @s: buffer that contains the command to parse
 *
 * Description: Parses a buffer containing shell
 *		commands
 * Return: An command structure
 */
struct cmd *parsecmd(char *s)
{
	char *es;
	struct cmd *cmd;

	es = s + _strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");

	if (s != es)
	{
		error("Syntax not correct");
		exit(1);
	}

	nulterminate(cmd);

	return (cmd);
}

/**
 * peek - Custom Function
 * @ps: pointer to the start of the string
 * @es: pointer to the somewhere on the string
 * @toks: list of tokens to look for
 *
 * Description: Scans for any characters that is not a
 *		whitespace
 * Return: An integer
 */
int peek(char **ps, char *es, char *toks)
{
	char *s, ws[] = WHITESPACE;

	s = *ps;

	while (s < es && _strchr(ws, *s))
		s++;

	*ps = s;

	return (*s && _strchr(toks, *s));

}

/**
 * gettoken - Custom Function
 * @ps: pointer to the start of the string
 * @es: pointer to the end of the string
 * @q: pointer to somewhere at the beginning of the string
 * @eq: pointer to somewhere at the end of the string
 *
 * Description: Iterates the string from the start in order
 *		to find specific tokens
 * Return: An integer
 */
int gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s, whitespace[] = WHITESPACE, symbols[] = TOKENS;
	int ret;

	s = *ps;

	while (s < es && _strchr(whitespace, *s))
		s++;

	if (q)
		*q = s;

	ret = *s;

	eval(s, es, &ret, whitespace, symbols);

	if (eq)
		*eq = s;

	while (s < es && _strchr(whitespace, *s))
		s++;

	*ps = s;

	return (ret);
}

/**
 * eval - Custom Function
 * @s: pointer to the start of the string
 * @es: pointer to the end of the string
 * @res: result value
 * @ws: list of whitespace chars to look for
 * @sym: list of symbols to look for
 *
 * Description: Evaluates the given char to see if it
 *		matches find specific tokens
 */
void eval(char *s, char *es, int *res, char *ws, char *sym)
{
	switch (*s)
	{
		case 0:
			break;
		case '|':
		case '(':
		case ')':
		case ';':
		case '&':
		case '<':
			s++;
			break;
		case '>':
			s++;
			if (*s == '>')
			{
				*res = '+';
				s++;
			}
			break;
		default:
			*res = 'a';

			while (s < es && !_strchr(ws, *s) &&
					!_strchr(sym, *s))
				s++;

			break;
	}
}

/**
 * nulterminate - Custom Function
 * @cmd: a command to null terminate
 *
 * Description: Replaces specific chars of a command
 *		with \0 to null terminate it
 *
 * Return: An command structure
 */
struct cmd *nulterminate(struct cmd *cmd)
{
	int i;
	struct execcmd *ecmd;
	struct listcmd *lcmd;
	struct pipecmd *pcmd;
	struct redircmd *rcmd;

	if (cmd == 0)
		return (0);

	switch (cmd->type)
	{
		case EXEC:
			ecmd = (struct execcmd *)cmd;

			for (i = 0; ecmd->argv[i]; i++)
				*ecmd->eargv[i] = 0;
		break;
		case REDIR:
			rcmd = (struct redircmd *)cmd;
			nulterminate(rcmd->cmd);
			*rcmd->efile = 0;
		break;
		case PIPE:
			pcmd = (struct pipecmd *)cmd;
			nulterminate(pcmd->left);
			nulterminate(pcmd->right);
		break;
		case LIST:
			lcmd = (struct listcmd *)cmd;
			nulterminate(lcmd->left);
			nulterminate(lcmd->right);
		break;
	}

	return (cmd);
}
