# hsh - Holberton Simple Shell

This project is a custom implementation of a simple UNIX command line interpreter (shell), written in C, as part of the **Holberton School** curriculum. It processes user commands and executes them using the system's process management features.

## Features

* **Command Execution:** Executes executable files found within the **$PATH** environment variable.
* **Absolute/Relative Path Execution:** Supports executing commands given with a full path (e.g., `/bin/ls`) or a relative path (e.g., `./script`).
* **Built-in Commands:**
    * **`exit`**: Exits the shell. It uses the status of the last executed command as the exit status.
    * **`env`**: Prints the current environment variables to standard output.
* **Command Tokenization:** Parses input lines into a null-terminated array of arguments using space and tab as delimiters.
* **Error Handling:** Displays an error message to `stderr` (`./hsh: 1: command: not found`) and sets the appropriate exit status (**127**) when a command is not found.
* **Interactive Mode Prompt:** Displays a simple `:) ` prompt in interactive mode.

## Files Description

| File Name | Description |
| :--- | :--- |
| `main.c` | Entry point of the shell. It calls the main shell loop function, `simple_shell`. |
| `shell.h` | The primary header file. Contains all function prototypes, includes necessary libraries, and defines constants (`MAX_ARGS`, `MAX_PATH`). |
| `shell.c` | Contains the main logic of the shell's infinite loop (`simple_shell`). Handles input reading, command parsing, built-in checks, process creation (`fork`), and status waiting (`waitpid`). |
| `parser.c` | Implements `parse_command`, which splits the input string into a list of arguments. |
| `find_command.c` | Implements `find_command`, which searches for the executable's full path within the `$PATH` environment variable. |
| `execute.c` | Implements `execute_command`, which attempts to execute the command and its arguments using `execve`. |
| `builtins.c` | Contains the logic for built-in commands: `is_builtin` checks for `exit` and `env`, and `handle_env` prints the environment. |
| `_getenv.c` | Implements `_getenv`, a custom function to retrieve the value of an environment variable. |
| `_strlen.c` | Custom function to calculate the length of a string. |
| `string_utils.c` | Custom function `_strcmp` for string comparison, used primarily to check built-in commands. |

## How to Compile and Run

### Compilation

To compile the project, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
