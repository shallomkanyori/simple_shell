/**
 * _myenv - prints the environment variables, each separated by a new line
 * @sh_data: a pointer to the structure containing the shell_data
 *
 * Return: -1 on error, 0 on success.
 */
int _myenv(shdata_t *sh_data)
{
	int i;
	char **env = sh_data->env;

	if (env == NULL)
		return (-1);
	for (i = 0; env[i]; i++)
	{
		if (putstr(env[i] == -1 || putchar('\n') == -1)
				return (-1);
	}
	return (0);
}
