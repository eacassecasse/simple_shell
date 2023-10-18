#include "main.h"

/**
 * _strncat - Custom function
 * @dest: pointer to the first char to concatenate
 * @src: pointer to the second char to concatenate
 * @n: size of characters to be concatenated
 *
 * Description: Concatenates *src to *dest removing '\0'
 * Return: *dest strings concatenated
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j, len;

	i = 0;
	j = 0;
	len = 0;

	while (dest[i] != '\0')
		i++;

	while (src[len] != '\0')
		len++;

	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}

	if (n < len)
		dest[i] = '\0';

	return (dest);
}
