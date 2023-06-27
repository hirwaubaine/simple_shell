#include "shell.h"
/**
 * builtinm - matches built-in command to its function
 * for exectution
 * @strr: built-in command
 * Return: 0 if it fails
 */
size_t builtinm(char **strr)
{
	int i = 0;

	builtin_t match[] = {
		{"exit", my_exit},
		{"setenviron", _setenviron},
		{NULL, NULL},
	};
	while (match[i].command)
	{
		if (_strcmp(match[i].command, strr[0]) == 0)
			return (match[i].fptr(strr));
		i++;
	}
	return (0);
}
