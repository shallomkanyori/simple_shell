#include "main.h"

/**
 * print_error - displays an error message
 * @sh_data: a pointer to the structure containing the shell data
 *
 * Return: Nothing.
 */
void print_error(shdata_t *sh_data)
{
	sh_data->res = errno;
	if (errno != 1 && errno != 2)
	{
		put_str_err(sh_data->av[0]);
		put_str_err(": ");
		put_str_err(itoa(sh_data->line_num, sh_data->line_num_str));
		put_str_err(": ");

		if (sh_data->err_incl_cmd)
		{
			put_str_err(sh_data->cmd[0]);
			put_str_err(": ");
			sh_data->err_incl_cmd = 0;
		}

		if (sh_data->err_message != NULL)
		{
			put_str_err(sh_data->err_message);
			put_chr_err('\n');
			put_chr_err(BUFF_FLUSH);
			sh_data->err_message = NULL;
		}
		else
		{
			put_chr_err(BUFF_FLUSH);
			perror("");
			fflush(stderr);
		}
	}
	else
	{
		perror(sh_data->av[0]);
		fflush(stderr);
	}
}

/**
 * put_str_err - write a string to stderr using a buffer
 * @str: the string to write
 *
 * Return: -1 on error, 0 on success
 */
int put_str_err(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
		if (put_chr_err(str[i]) == -1)
			return (-1);

	return (0);
}

/**
 * put_chr_err - writes a character to stderr using a buffer
 * @c: the character
 *
 * Return: -1 on error, positive number on success.
 */
int put_chr_err(char c)
{
	static char buffer[BUFF_SIZE];
	static int i;
	int res = 1;

	if (i == BUFF_SIZE || c == BUFF_FLUSH)
	{
		res = write(STDERR_FILENO, buffer, i);
		i = 0;
	}

	if (c != BUFF_FLUSH)
		buffer[i++] = c;
	return (res);
}
