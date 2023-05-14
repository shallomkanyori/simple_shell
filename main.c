#include "main.h"

/**
 * parse_input - parses input into a list containing the command name
 * and NULL
 * @input: the input
 * @cmd: a pointer to where to store the result
 * @av: the program arguments for error handling
 * @res: a pointer to the return value of main for error handling
 *
 * Return: nothing.
 */
void parse_input(char *input, char ***cmd, char **av, int *res)
{
	char *delim = " \n";
	char *input_cpy;
	char *token;
	int argc = 0;
	int i = 0;

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

	*cmd = realloc(*cmd, sizeof(char *) * (argc + 1));
	if (*cmd == NULL)
	{
		print_error(av, res);
		return;
	}

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
 * exec_cmd - executes the given command
 * @cmd: a list containing the command name and NULL
 * @av: the program arguments
 * @env: the environment variables
 * @res: a pointer to the return value of main for error handling
 *
 * Return: 0 on success, non-zero on failure.
 */
int exec_cmd(char **cmd, char **av, char **env, int *res)
{
	int child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		execve(cmd[0], cmd, env);
		print_error(av, res); /* if execve returns, there is an error */
		exit(*res); /* use the errno stored in res */
	}
	else if (child_pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	else
	{
		print_error(av, res);
		return (*res);
	}
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

		parse_input(input, &cmd, av, &res);
		if (cmd == NULL || cmd[0] == NULL)
			continue;

		res = exec_cmd(cmd, av, env, &res);
	}

	free(input);
	free(cmd);
	input = NULL;
	cmd = NULL;
	return (res);
}
