/**
 * _strcpy - Custom function
 * @dest: pointer to the first param to swap
 * @src: pointer to the second param to swap
 *
 * Description: Copies a string to the buffer
 * Return: char *
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return (dest);
}
