#include "main.h"

/**
 * handle_cmd - handles the interpretation and execution of a command
 * @cmd: an array containing the command and its arguments
 * @av: the program arguments for error handling
 * @env: the environment variables
 * @res: a pointer to the return value of main for error handling.
 *
 * Return: 0 on success, non_zero on failure.
 */
int handle_cmd(char **cmd, char **av, char **env, int *res)
{
	char *path = NULL;
	char *full_path = NULL;
	int result = 0;

	path = get_path(env);
	if (path != NULL)
		search_path(path, &full_path, cmd, av, res);

	/* check if command executable found */
	if (access(cmd[0], F_OK) != 0)
	{
		*res = 127;
		if (write(STDERR_FILENO, av[0], _strlen(av[0])) == -1 ||
			write(STDERR_FILENO, ": ", 2) == -1 ||
			write(STDERR_FILENO, cmd[0], _strlen(cmd[0])) == -1 ||
			write(STDERR_FILENO, ": not found\n", 12) == -1)
			print_error(av, res);

		free_ptr((void **)&full_path);

		return (*res);
	}

	result = exec_cmd(cmd, av, env, res);
	free_ptr((void **)&full_path);

	return (result);
}

/**
 * exec_cmd - executes the given command
 * @cmd: and array containing the command and its arguments
 * @av: the program arguments for error handling
 * @env: the environment variables
 * @res: a pointer to the return value of main for error handling
 *
 * Return: 0 on success, non-zero on error.
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
		return (*res); /* use the errno stored in res */
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
 * get_path - gets the value of the PATH environment variable
 * @env: the environment variables
 *
 * Return: the value of the PATH variable or NULL.
 */
char *get_path(char **env)
{
	char *path_str = "PATH";
	int len = _strlen(path_str);
	int i;

	for (i = 0; env && env[i]; i++)
		if (_strncmp(env[i], path_str, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);

	return (NULL);
}

/**
 * search_path - searches the directories in PATH for a command executable
 * @path: the value of the PATH variable, the directories to look through
 * @full_path: a pointer to the string that will hold the full path of the
 * executable
 * @cmd: an array containing the command and its arguments
 * @av: the program arguments for error handling
 * @res: a pointer to the return value of main for error handling
 *
 * Return: nothing.
 */
void search_path(char *path, char **full_path, char **cmd, char **av, int *res)
{
	char *path_cpy, *path_token, *full_path_res;
	unsigned int s_old = 0, s_new = 0;

	/* check if the command is a relative or absolute path */
	if (_strchr(cmd[0], '/') != NULL)
		return;

	path_cpy = _strdup(path);
	if (path_cpy == NULL)
	{
		print_error(av, res);
		return;
	}

	path_token = strtok(path_cpy, ":");
	while (path_token)
	{
		s_new = sizeof(char) * (_strlen(path_token) + _strlen(cmd[0]) + 2);
		full_path_res = _realloc(*full_path, s_old, s_new);
		if (full_path_res == NULL)
		{
			free_ptr((void **)&path_cpy);
			print_error(av, res);
			return;
		}

		*full_path = full_path_res;
		_strcpy(*full_path, path_token);
		_strcat(*full_path, "/");
		_strcat(*full_path, cmd[0]);
		if (access(*full_path, F_OK) == 0)
		{
			cmd[0] = *full_path;
			break;
		}

		s_old = s_new;
		path_token = strtok(NULL, ":");
	}
	free_ptr((void **)&path_cpy);
}
