#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_ARGS 64
#define MAX_PATH 1024

/* Prototypes */
void simple_shell(void);
char **parse_command(char *line);
char *find_command(char *command);
void execute_command(char **argv);

extern char **environ;

#endif /* SHELL_H */
