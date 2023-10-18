#include "main.h"

/**
 * _strcmp - Custom function
 * @s1: pointer to the first char to compare
 * @s2: pointer to the second char to compare
 *
 * Description: Compares *s1 and *s2
 * Return: random number that indicates:
 * < 0 if s1 less than s2
 * > 0 if s2 less than s1
 * 0 if s2 equal to s1
 */

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}
