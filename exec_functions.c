#include "main.h"

/**
 * handle_cmd - handles the interpretation and execution of a command
 * @sh_data: a pointer to the structure containing the shell data
 *
 * Return: 0 on success, non_zero on failure.
 */
int handle_cmd(shdata_t *sh_data)
{
	char *full_path = NULL;
	char *cmd_path = NULL;
	int path_found = 0;
	int result = 0;

	if (sh_data->path == NULL)
		sh_data->path = get_path(sh_data->env);

	if (sh_data->path != NULL)
		search_path(sh_data, &full_path, &path_found);

	cmd_path = path_found ? full_path : sh_data->cmd[0];

	/* check if command executable found */
	if (access(cmd_path, F_OK) != 0)
	{
		errno = 127;
		sh_data->err_message = "not found";
		sh_data->err_incl_cmd = 1;
		print_error(sh_data);

		free_ptr((void **)&full_path);
		return (sh_data->res);
	}

	result = exec_cmd(sh_data, cmd_path);
	free_ptr((void **)&full_path);
	return (result);
}

/**
 * exec_cmd - executes the given command
 * @sh_data: a pointer to the structure containing the shell data
 * @cmd_path: the full path to the command executable
 *
 * Return: 0 on success, non-zero on error.
 */
int exec_cmd(shdata_t *sh_data, char *cmd_path)
{
	int child_pid;
	int status;

	child_pid = fork();
	if (child_pid == 0)
	{
		execve(cmd_path, sh_data->cmd, sh_data->env);

		if (errno == EACCES)
		{
			errno = 126;
			sh_data->err_message = "Permission denied";
			sh_data->err_incl_cmd = 1;
		}

		print_error(sh_data); /* if execve returns, there is an error */
		return (sh_data->res); /* use the errno stored in res */
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
		print_error(sh_data);
		return (sh_data->res);
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
 * @sh_data: a pointer to the structure containing the shell data
 * @full_path: a pointer to the string that will hold the full path of the
 * executable
 * @found: a pointer to the flag for whether or not an executable is found
 *
 * Return: nothing
 */
void search_path(shdata_t *sh_data, char **full_path, int *found)
{
	char *path_cpy, *path_token, *full_path_res;
	unsigned int s_old = 0, s_new = 0;

	if (_strchr(sh_data->cmd[0], '/') != NULL) /* if command is already a path */
		return;

	path_cpy = _strdup(sh_data->path);
	if (path_cpy == NULL)
	{
		print_error(sh_data);
		return;
	}

	path_token = strtok(path_cpy, ":");
	while (path_token)
	{
		s_new = sizeof(char) * (_strlen(path_token) + _strlen(sh_data->cmd[0]) + 2);
		full_path_res = _realloc(*full_path, s_old, s_new);
		if (full_path_res == NULL)
		{
			print_error(sh_data);
			free_ptr((void **)&path_cpy);
			return;
		}

		*full_path = full_path_res;
		_strcpy(*full_path, path_token);
		_strcat(*full_path, "/");
		_strcat(*full_path, sh_data->cmd[0]);
		if (access(*full_path, F_OK) == 0)
		{
			*found = 1;
			break;
		}

		s_old = s_new;
		path_token = strtok(NULL, ":");
	}
	free_ptr((void **)&path_cpy);
}
