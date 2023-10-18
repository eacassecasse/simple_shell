#include <stdio.h>

/**
 * _strlen - Custom function
 * @s: pointer to an char to count
 *
 * Description: Counts string
 * Return: int
 */
int _strlen(char *s)
{
	int length;

	length = 0;

	while (*s != '\0')
	{
		length++;
		s++;
	}

	return (length);
}
