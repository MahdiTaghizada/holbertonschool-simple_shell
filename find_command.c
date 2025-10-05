#include "shell.h"

/**
 * find_command - search command in PATH
 * @command: command name
 *
 * Return: full path if found, NULL otherwise
 */
char *find_command(char *command)
{
	char *path_env, *path_copy, *dir;
	static char fullpath[MAX_PATH];

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (command);
		else
			return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(fullpath, MAX_PATH, "%s/%s", dir, command);
		if (access(fullpath, X_OK) == 0)
		{
			free(path_copy);
			return (fullpath);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
