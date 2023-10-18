#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"


/**
 * readIn - Custom function
 * @buf: String to hold the input
 *
 * Description: Reads the input from user
 */
void readIn(char **buf)
{
	size_t n = 100;
	int i = 0;
	*buf = malloc(sizeof(char) * n);

	if (!(*buf))
	{
		error("Failed to allocate memory");
		exit(1);
	}

	if (getline(buf, &n, stdin) < 0)
	{
		error("Failed to read the inputs");
		free(buf);
		exit(1);
	}
}

