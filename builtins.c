#include "shell.h"

/**
 * is_builtin - checks if the command is a built-in
 * @argv: argument vector (parsed command and arguments)
 * @line: The input line buffer (needed for freeing memory before exiting).
 * @last_status: Pointer to the last exit status of the previous command.
 *
 * Return: 1 if built-in command was executed, 0 otherwise.
 */
int is_builtin(char **argv, char *line, int *last_status)
{
	if (_strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(*last_status);
	}

	if (_strcmp(argv[0], "env") == 0)
	{
		handle_env();
		*last_status = 0;
		return (1);
	}
	return (0);
}

/**
 * handle_env - prints the current environment variables
 */
void handle_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
