#include "main.h"

/**
 * _memset - Custom function
 * @s: pointer to a string that must be transformed
 * @b: pointer to the char to replace with on the string
 * @n: number of bytes that must be replaced
 *
 * Description: Replaces n bytes from a string ith a given char
 * Return: Transformed string
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;

		i++;
	}

	return (s);
}
