#include "main.h"

/**
 * memCpy - takes information btw void pointer
 * @nptr: dest ptr
 * @ptr: src ptr
 * @size: size of the new ptr
 * Return: no return.
 */
void memCpy(void *nptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_nptr = (char *)nptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_nptr[i] = char_ptr[i];
}

/**
 * Realloc - allocate new  memory block.
 * @ptr: ptr to the previously allocated mem.
 * @old_size:old allocated space of ptr.
 * @new_size: new allocated memory block.
 * Return: Return: returns a ptr or NULL.
 */
void *Realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		memCpy(newptr, ptr, new_size);
	else
		memCpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * Reallocdp - allocates a memory block of a ptr to another ptr.
 * @ptr: double pointer to the old mem allocated.
 * @new_size: new size, in bytes, of the new memory block.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * Return: returns a ptr or NULL.
 */
char **Reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
