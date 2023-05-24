#include "main.h"

/**
 * parse_input - parses input into a list containing the command name
 * and NULL
 * @sh_data: a pointer to the shell data structure
 * @s_old: a pointer to the prev size of cmd, for realloc
 *
 * Return: nothing.
 */
void parse_input(shdata_t *sh_data, unsigned int *s_old)
{
	char *delim = " \t\n";
	char *input_cpy, *token;
	int argc = 0, i = 0;
	unsigned int s_new;
	char **cmd_res;

	input_cpy = _strdup(sh_data->input);
	if (input_cpy == NULL)
	{
		print_error(sh_data);
		return;
	}

	token = strtok(input_cpy, delim);
	while (token)
	{
		argc++;
		token = strtok(NULL, delim);
	}

	s_new = sizeof(char *) * (argc + 1);
	cmd_res = _realloc(sh_data->cmd, *s_old, s_new);
	if (cmd_res == NULL)
	{
		print_error(sh_data);
		return;
	}

	sh_data->cmd = cmd_res;
	*s_old = s_new;
	token = strtok(sh_data->input, delim);
	while (token)
	{
		sh_data->cmd[i++] = token;
		token = strtok(NULL, delim);
	}

	sh_data->cmd[i] = NULL;
	free(input_cpy);
}

/**
 * init_shdata - initialized the shdata_t, the shell data structure
 * @sh_data: a pointer to the structure to initialize
 * @av: the program arguments
 * @env: the environment variables
 *
 * Return: nothing.
 */
void init_shdata(shdata_t *sh_data, char **av, char **env)
{
	sh_data->av = av;
	sh_data->env = env;
	sh_data->cmd = NULL;
	sh_data->input = NULL;
	sh_data->path = NULL;
	sh_data->interactive = isatty(STDIN_FILENO);
	sh_data->line_num = 0;
	sh_data->res = 0;
	sh_data->err_message = NULL;
	sh_data->err_incl_cmd = 0;
}

/**
 * free_shdata - frees the malloc'ed shell data
 * @sh_data: a pointer to the shell data structure
 *
 * Return: nothing.
 */
void free_shdata(shdata_t *sh_data)
{
	free_ptr((void **)&sh_data->input);
	free_ptr((void **)&sh_data->cmd);
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
	shdata_t sh_data;
	size_t input_len = 0;
	unsigned int s_old = 0; /* holds prev size of cmd array for realloc */

	(void) ac;

	init_shdata(&sh_data, av, env);
	while (1)
	{
		sh_data.line_num++;
		if (sh_data.interactive)
		{
			if (write(STDOUT_FILENO, "$ ", 2) == -1)
			{
				print_error(&sh_data);
				continue;
			}
		}

		errno = 0; /* ensures that errno is 0 if getline encounters EOF */
		if (getline(&sh_data.input, &input_len, stdin) == -1)
		{
			if (errno == 0 || (errno == ENOTTY && !sh_data.interactive))
				break;

			print_error(&sh_data);
			continue;
		}

		parse_input(&sh_data, &s_old);
		if (sh_data.cmd == NULL || sh_data.cmd[0] == NULL)
			continue;

		sh_data.res = handle_cmd(&sh_data);
	}

	free_shdata(&sh_data);
	return (sh_data.res);
}
