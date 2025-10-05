#include "shell.h"

/**
 * find_command - search command in PATH
 * @command: command name
 *
 * Return: full path if found (MUST BE FREED BY CALLER), NULL otherwise
 */
char *find_command(char *command)
{
	char *path_env, *path_copy, *dir;
	char *full_path_result;
	int len;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		else
			return (NULL);
	}

	path_env = _getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = _strlen(dir) + _strlen(command) + 2;
		full_path_result = malloc(len);
		if (!full_path_result)
		{
			free(path_copy);
			return (NULL);
		}
		
		sprintf(full_path_result, "%s/%s", dir, command);

		if (access(full_path_result, X_OK) == 0)
		{
			free(path_copy);
			return (full_path_result);
		}

		free(full_path_result);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}