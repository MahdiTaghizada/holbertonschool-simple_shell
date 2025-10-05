#include "shell.h"

/**
 * simple_shell - main loop of shell
 */
int simple_shell(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **argv;
	pid_t pid;
	int status;
	int last_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, ":) ", 3);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] == '\0')
			continue;

		argv = parse_command(line);
		if (argv[0] == NULL)
			continue;

		if (is_builtin(argv))
		{
			continue;
		}

		if (find_command(argv[0]) == NULL)
		{
			write(STDERR_FILENO, "./hsh: 1: ", 10);
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": not found\n", 12);
			last_status = 127;
			continue;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(line);
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			execute_command(argv);
			perror("./shell");
			exit(127);
		}
		else
			waitpid(pid, &status, 0);
	}
	return (last_status);
}
