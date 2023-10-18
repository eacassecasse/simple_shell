#include "main.h"

/**
 * _puts - Custom function
 * @str: pointer to an char to print
 *
 * Description: Prints a given string
 * Return: void
 */
void _puts(char *str)
{

	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
}
