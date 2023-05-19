#include "main.h"

/**
 * _strchr - locates a character in a string
 * @str: the string
 * @c: the character
 *
 * Return: apointer to the first occurrence of c in str or NULL if c is not
 * found.
 */
char *_strchr(char *str, char c)
{
	int i;

	for (i = 0; str[i]; i++)
		if (str[i] == c)
			return (&str[i]);

	return (NULL);
}

/**
 * _memcpy - copies a memory ares
 * @dest: a pointer to the memory area to copy to
 * @src: a pointer to the memory area to copy from
 * @n: the number of bytes to copy
 *
 * Return: a pointer to dest.
 */
void *_memcpy(void *dest, void *src, unsigned int n)
{
	unsigned int i;
	char *d_ptr = (char *)dest;
	char *s_ptr = (char *)src;

	for (i = 0; i < n; i++)
		d_ptr[i] = s_ptr[i];

	return (dest);
}
