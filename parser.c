#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * parser - Custom Function
 * @str: String to parsed
 * @delim: The delimiter string of where to parse the string
 *
 * Description: Parses the given string into tokens
 *		based on give delimiter
 * Return: An array with the extracted tokens
 *	or NULL in case of failure
 */
char **parser(char *str, char *delim)
{
	char *token = NULL, *str_cpy;
	int counter = 0, i = 0;
	char **tokens = NULL;

	str_cpy = strdup(str);

	token = strtok(str, delim);

	while (token)
	{
		token = strtok(NULL, delim);
		counter++;
	}

	if (counter > 0)
	{
		tokens = malloc(sizeof(char *) * counter);

		if (!tokens)
			return (NULL);

		token = strtok(str_cpy, delim);

		while (token)
		{
			tokens[i] = token;
			token = strtok(NULL, delim);
			i++;
		}

		tokens[i] = NULL;
	 }

	return (tokens);
}

/**
 * parseSeq - Custom Function
 * @line: line to parse
 *
 * Description: Parses the shell arguments using the
 *		parser(char *str, char *delim) function
 * Return: An array of argument tokens or NULL
 */
char **parseSeq(char *line)
{
	char *delim = ";\n";
	size_t n = 0;
	char **argv = NULL;

	argv = parser(line, delim);

	if (!argv)
		return (NULL);

	return (argv);
}

/**
 * parsePipe - Entry Point
 * @cmd: command to parse
 *
 * Description: Parses the shell arguments using the
 *		parser(char *str, char *delim) function
 * Return: An array of argument tokens or NULL
 */
char **parsePipe(char *cmd)
{
	char *delim = "|\n";
	size_t n = 0;
	char **argv = NULL;

	argv = parser(cmd, delim);

	if (!argv)
		return (NULL);

	return (argv);
}

/**
 * parseLine - Entry Point
 * @line: command to parse
 *
 * Description: Parses the shell arguments using the
 *		parser(char *str, char *delim) function
 * Return: An array of argument tokens or NULL
 */
char **parseLine(char *cmd)
{
	char *delim = " \n";
	size_t n = 0;
	char **argv = NULL;

	argv = parser(cmd, delim);

	if (!argv)
		return (NULL);

	return (argv);
}

