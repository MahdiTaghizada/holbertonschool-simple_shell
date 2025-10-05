#include "shell.h"

/**
 * _strlen - computes the length of a string
 * @s: the string whose length to check
 *
 * Return: the length of the string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;
	return (len);
}
