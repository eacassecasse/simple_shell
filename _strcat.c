#include "main.h"

/**
 * _strcat - Custom function
 * @dest: pointer to the first char to concatenate
 * @src: pointer to the second char to concatenate
 *
 * Description: Concatenates *src to *dest removing '\0'
 * Return: *dest strings concatenated
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	j = 0;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}

	dest[i] = '\0';

	return (dest);
}
