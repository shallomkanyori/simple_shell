#include "main.h"

/**
 * _strdup - duplicates a string
 * @str: the str to be duplicated
 *
 * Return: A pointer to the duplicated string if str is not NULL and
 * sufficient memory is available. Otherwise, returns NULL.
 */
char *_strdup(char *str)
{
	char *res;
	int i;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i]; i++)
		;

	res = malloc(sizeof(char) * i + 1);
	if (res == NULL)
		return (NULL);

	for (i = 0; str[i]; i++)
		res[i] = str[i];

	res[i] = '\0';
	return (res);
}

/**
 * _strlen - returns the length of a string
 * @str: the string
 *
 * Return: the length of str
 */
int _strlen(char *str)
{
	int len;

	for (len = 0; str[len]; len++)
		;

	return (len);
}

/**
 * _strncmp - compares at most n bytes from two strings
 * @s1: the first string
 * @s2: the second string
 * @n: the number of bytes to compare
 *
 * Return: 0 if the strings are equal, a negative number if s1 is less than s2
 * and a positive number if s1 is greater than s2.
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL)
		return (-1);
	else if (s2 == NULL)
		return (1);

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);

		if (s1[i] == '\0')
			break;
	}

	return (0);
}

/**
 * _strcpy - copies one string to another
 * @dest: the string to copy to
 * @src: the string to copy from
 *
 * Return: a pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}

/**
 * _strcat - appends one string to another
 * @dest: the string to append to
 * @src: the string to be appended
 *
 * Return: a pointer to the resulting string dest.
 */
char *_strcat(char *dest, char *src)
{
	int i;
	int len = _strlen(dest);

	for (i = 0; src[i]; i++)
		dest[len + i] = src[i];

	dest[len + i] = '\0';
	return (dest);
}
