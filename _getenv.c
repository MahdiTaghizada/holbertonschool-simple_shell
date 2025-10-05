#include "shell.h"

/**
 * _getenv - gets an environment variable
 * @name: the name of the environment variable to find
 *
 * Return: pointer to the value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	size_t name_len = 0;
	while (name[name_len] != '\0')
		name_len++;
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
	}
	return (NULL);
}
