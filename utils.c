#include "main.h"

/**
 * itoa - converts an unsigned integer to a string
 * @n: the integer
 * @res: where to store the resulting string
 *
 * Return: the string conversion of the integer.
 */
char *itoa(unsigned int n, char *res)
{
	int i = INT_STR_SIZE - 1;

	res[i--] = '\0';

	if (n == 0)
		res[i--] = '0';

	while (n > 0)
	{
		res[i--] = (n % 10) + '0';
		n /= 10;
	}

	i++;
	return (&res[i]);
}
