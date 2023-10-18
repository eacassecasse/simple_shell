/**
 * _strncpy - Custom function
 * @dest: pointer to the first param to swap
 * @src: pointer to the second param to swap
 * @n: number of characters to copy
 *
 * Description: Copies a string to the buffer
 * Return: char *
 */
char *_strncpy(char *dest, char *src, int n)
{
	int len;

	len = 0;


	while (len < n && src[len] != '\0')
	{
		dest[len] = src[len];
		len++;
	}

	while (len < n)
	{
		dest[len] = '\0';
		len++;
	}

	return (dest);
}
