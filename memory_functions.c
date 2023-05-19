#include "main.h"

/**
 * _realloc - reallocates a memory block
 * @ptr: the pointer to the memory previously allocated with malloc
 * @s_old: the size in bytes of ptr
 * @s_new: the size in bytes of the new memory block
 *
 * Return: a pointer to the new memory block or NULL if the allocation fails.
 */
void *_realloc(void *ptr, unsigned int s_old, unsigned int s_new)
{
	void *res;
	unsigned int size;

	if (s_old == s_new)
		return (ptr);

	if (s_new == 0)
	{
		free(ptr);
		return (NULL);
	}

	res = malloc(s_new);
	if (res == NULL)
		return (NULL);

	if (ptr == NULL)
		return (res);

	size = s_old < s_new ? s_old : s_new;

	_memcpy(res, ptr, size);
	free(ptr);

	return (res);
}

/**
 * free_ptr - frees a pointer
 * @ptr: a pointer to the pointer
 *
 * Return: nothing.
 */
void free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
