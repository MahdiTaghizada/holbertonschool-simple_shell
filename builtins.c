#include "shell.h"

/**
 * is_builtin - checks if the command is a built-in
 * @argv: argument vector
 *
 * Return: 1 if built-in, 0 otherwise
 */
int is_builtin(char **argv)
{
	if (_strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(0);
	}
	return (0);
}
