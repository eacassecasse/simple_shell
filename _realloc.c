#include "main.h"
#include <stdlib.h>
#include <stddef.h>

/**
 * _realloc - Custom function
 * @ptr: Pointer to a memory previously allocated
 * @old_size: Bytes allocated to ptr previously
 * @new_size: Bytes to allocate to the memory block
 *
 * Description: Reallocates a new memory block to a pointer
 * Return: A pointer to new allocated memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *old_ptr, *new_ptr;
	unsigned int count;

	if (old_size == new_size)
		return (ptr);

	if (ptr && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc((new_size));

	if (!ptr)
		return (new_ptr);

	if (!new_ptr)
		return (NULL);

	old_ptr = ptr;

	if (old_size > new_size)
	{
		for (count = 0; count < new_size; count++)
			new_ptr[count] = old_ptr[count];
	}
	else if (old_size < new_size)
	{
		for (count = 0; count < old_size; count++)
			new_ptr[count] = old_ptr[count];
	}

	free(ptr);

	return (new_ptr);
}


