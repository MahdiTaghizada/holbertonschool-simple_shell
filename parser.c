#include "shell.h"

/**
 * parse_command - split line into arguments
 * @line: input string
 *
 * Return: NULL-terminated array of arguments (static)
 */
char **parse_command(char *line)
{
	static char *argv[MAX_ARGS];
	char *token;
	int i, argc = 0;

	for (i = 0; i < MAX_ARGS; i++)
		argv[i] = NULL;

	token = strtok(line, " \t");
	while (token != NULL && argc < MAX_ARGS - 1)
	{
		argv[argc] = token;
		argc++;
		token = strtok(NULL, " \t");
	}

	argv[argc] = NULL;
	return (argv);
}
