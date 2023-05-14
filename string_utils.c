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
