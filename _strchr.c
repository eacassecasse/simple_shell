#include "main.h"
#include <stddef.h>

/**
 * _strchr - Custom function
 * @s: pointer to a string that must be transformed
 * @b: character to search for
 *
 * Description: Search for a given charactr
 * Return: A pointer to the first occurence of the chararcter
 */

char *_strchr(char *s, char b)
{
	int c;

	while (1)
	{
		c = *s++;

		if (c == b)
		{
			return (s - 1);
		}

		if (c == 0)
			return (NULL);
	}
}
