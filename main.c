#include "main.h"

/**
 * print_error - displays an error message
 * @av: the program arguments
 *
 * Return: nothing.
 */
void print_error(char **av)
{
	perror(av[0]);
	fflush(stdout);
}

/**
 * parse_input - parses input into a list containing the command name
 * and NULL
 * @input: the input
 * @cmd: where to store the result
 *
 * Return: nothing.
 */
void parse_input(char *input, char **cmd)
{
	cmd[0] = strtok(input, "\n");
	cmd[1] = NULL;
}

/**
 * exec_cmd - executes the given command
 * @cmd: a list containing the command name and NULL
 * @av: the program arguments
 * @env: the environment variables
 *
 * Return: 0 on success, non-zero on failure.
 */
int exec_cmd(char **cmd, char **av, char **env)
{
	int child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		execve(cmd[0], cmd, env);
		print_error(av); /* if execve returns, there is an error */
		exit(errno);
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
		print_error(av);
		return (errno);
	}
}

/**
 * main - A simple shell
 * @ac: the number of program arguments
 * @av: the program arguments
 * @env: the environment variables
 *
 * Return: 0 on success, non-zero on error.
 */
int main(int ac, char **av, char **env)
{
	int interactive = isatty(STDIN_FILENO);
	char *input = NULL;
	size_t input_len = 0;
	char *cmd[2]; /* handle one word arguments only for now */
	int res;

	(void) ac;
	while (1)
	{
		if (interactive)
		{
			printf("$ ");
			fflush(stdout);
		}

		read_res = getline(&input, &input_len, stdin);
		if (read_res == -1)
		{
			if (errno == 0 || (errno == ENOTTY && !interactive))
				break;

			res = errno;
			print_error(av);
			continue;
		}

		parse_input(input, cmd);
		if (cmd[0] == NULL)
			continue;

		res = exec_cmd(cmd, av, env);
	}

	free(input);
	input = NULL;
	return (res);
}
