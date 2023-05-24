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

/**
 * _strcmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: 0 if the strings are equal, a negative number is s2 is greater than
 * s1 and a positive number if s1 is greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL)
		return (-1);
	else if (s2 == NULL)
		return (1);

	for (i = 0; s1[i] && s1[i] == s2[i]; i++)
		;

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
