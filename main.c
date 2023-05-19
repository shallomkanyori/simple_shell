#include "main.h"

/**
 * parse_input - parses input into a list containing the command name
 * and NULL
 * @input: the input
 * @cmd: a pointer to where to store the result
 * @av: the program arguments for error handling
 * @res: a pointer to the return value of main for error handling
 * @s_old: a pointer to the prev size of cmd, for realloc
 *
 * Return: nothing.
 */
void parse_input(char *input, char ***cmd, char **av, int *res,
		unsigned int *s_old)
{
	char *delim = " \t\n";
	char *input_cpy, *token;
	int argc = 0, i = 0;
	unsigned int s_new;
	char **cmd_res;

	input_cpy = _strdup(input);
	if (input_cpy == NULL)
	{
		print_error(av, res);
		return;
	}

	token = strtok(input_cpy, delim);
	while (token)
	{
		argc++;
		token = strtok(NULL, delim);
	}

	s_new = sizeof(char *) * (argc + 1);
	cmd_res = _realloc(*cmd, *s_old, s_new);
	if (cmd_res == NULL)
	{
		print_error(av, res);
		return;
	}

	*cmd = cmd_res;
	*s_old = s_new;
	token = strtok(input, delim);
	while (token)
	{
		(*cmd)[i++] = token;
		token = strtok(NULL, delim);
	}

	(*cmd)[i] = NULL;
	free(input_cpy);
}

/**
 * main - A simple shell
 * @ac: the number of program arguments
 * @av: the program arguments
 * @env: the environment variables
 *
 * Return: The status of its last child, or 0 if no children.
 */
int main(int ac, char **av, char **env)
{
	int interactive = isatty(STDIN_FILENO);
	char *input = NULL;
	size_t input_len = 0;
	char **cmd = NULL;
	int res = 0;
	unsigned int s_old = 0; /* holds prev size of cmd array for realloc */

	(void) ac;
	while (1)
	{
		if (interactive)
		{
			if (write(STDOUT_FILENO, "$ ", 2) == -1)
			{
				print_error(av, &res);
				continue;
			}
		}

		errno = 0; /* ensures that errno is 0 if getline encounters EOF */
		if (getline(&input, &input_len, stdin) == -1)
		{
			if (errno == 0 || (errno == ENOTTY && !interactive))
				break;

			print_error(av, &res);
			continue;
		}

		parse_input(input, &cmd, av, &res, &s_old);
		if (cmd == NULL || cmd[0] == NULL)
			continue;

		res = handle_cmd(cmd, av, env, &res);
	}

	free_ptr((void **)&input);
	free_ptr((void **)&cmd);
	return (res);
}
