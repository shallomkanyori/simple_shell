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
