#include "shell.h"

/**
 * execute_command - execute the command
 * @argv: argument vector
 */
void execute_command(char **argv)
{
	execve(find_command(argv[0]), argv, environ);
}
