#include <stdio.h>
#include "main.h"

/**
 * _atoi - Custom function
 * @s: pointer to an char to convert
 *
 * Description: Convert a given string into integer
 * Return: int - extracted number or 0
 */
int _atoi(char *s)
{
	int i, f, length, res, sign, dVal;

	i = 0;
	length = 0;
	dVal = 0;
	res = 0;
	sign = 0;
	f = 0;

	while (s[length] != '\0')
		length++;

	while (i < length && f == 0)
	{
		if (s[i] == '-')
			++sign;

		if (s[i] >= '0' && s[i] <= '9')
		{
			dVal = s[i] - '0';

			if (sign % 2)
				dVal = -dVal;

			res = res * 10 + dVal;
			f = 1;

			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}

		i++;
	}

	if (f == 0)
		return (0);

	return (res);
}
