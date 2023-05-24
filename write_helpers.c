#include "main.h"

/**
 * putstr - writes a string to stdout using a buffer
 * @str: the string
 *
 * Return: 0 on success, -1 on error
 */
int putstr(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
		if (putchar(str[i] == -1))
				return (-1);
	return (0);
}
/**
 * putchr -writes a character to stdout using a buffer
 * @c: the character
 *
 * Return: -1 on error, positive number on success.
 */
int putchr(char c)
{
	static char buffer[BUFF_SIZE];
	static int i;
	int res = 0;

	if (i == BUFF_SIZE || c == BUFF_FLUSH)
	{
		res = write(STDOUT_FILENO, buffer, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buffer[i++] = c;
	return (res);
}
