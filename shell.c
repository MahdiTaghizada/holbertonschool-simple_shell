#include "shell.h"

/**
 * read_and_check_input - reads line, handles EOF and newlines
 * @line: pointer to buffer
 * @len: pointer to buffer size
 *
 * Return: 0 on success, -1 on EOF or error, 1 if empty line, 2 if newline removed.
 */
int read_and_check_input(char **line, size_t *len)
{
    ssize_t read;

    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, ":) ", 3);

    read = getline(line, len, stdin);
    if (read == -1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "\n", 1);
        free(*line);
        *line = NULL;
        return (-1);
    }

    if ((*line)[read - 1] == '\n')
    {
        (*line)[read - 1] = '\0';
        return (0); // Normal oxuma
    }

    return (0);
}

/**
 * execute_external_command - forks and executes a command
 * @argv: array of command and its arguments
 * @last_status: pointer to the last exit status
 */
void execute_external_command(char **argv, int *last_status)
{
    pid_t pid;
    int status;
    char *full_path;

    full_path = find_command(argv[0]);

    if (full_path == NULL)
    {
        write(STDERR_FILENO, "./hsh: 1: ", 10);
        write(STDERR_FILENO, argv[0], _strlen(argv[0]));
        write(STDERR_FILENO, ": not found\n", 12);
        *last_status = 127;
        return;
    }

    pid = fork();
    if (pid == -1)
	{
        perror("fork");
        free(full_path);
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        execve(full_path, argv, environ);
        perror("./shell");
        free(full_path);
        exit(127);
    }

    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            *last_status = WEXITSTATUS(status);
    }

    free(full_path);
}


/**
 * simple_shell - main loop of shell
 *
 * Return: last exit status
 */
int simple_shell(void)
{
    char *line = NULL;
    size_t len = 0;
    char **argv;
    int last_status = 0;

    while (1)
    {
        if (read_and_check_input(&line, &len) == -1)
            break;

        if (line == NULL || line[0] == '\0')
            continue;

        argv = parse_command(line);
        if (argv == NULL || argv[0] == NULL)
        {
            free(line);
            line = NULL;
            continue;
        }

        if (is_builtin(argv, line, &last_status))
        {
            free(line);
            line = NULL;
            continue;
        }

        execute_external_command(argv, &last_status);
        if (line)
        {
            free(line);
            line = NULL;
        }
    }

    return (last_status);
}
