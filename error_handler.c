#include "main.h"

/**
 * print_error - displays an error message
 * @av: the program arguments
 * @res: a pointer to the return value of main
 *
 * Return: Nothing.
 */
void print_error(char **av, int *res)
{
	*res = errno;
	perror(av[0]);
	fflush(stderr);
}
