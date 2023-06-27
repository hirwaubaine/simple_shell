#include "shell.h"
/**
 * my_exit - cause normal process termination
 * @strr: command received from terminal
 * Return: 0 if exit command is not found
 */
size_t my_exit(char **strr)
{
	if (!strr[1])
		exit(EXIT_SUCCESS);
	else
	{
		if (_atoi(strr[1]) == 0)
			return (0);
		exit(_atoi(strr[1]));
	}
	return (0);
}

/**
 * setenviron - change or add an environment variable
 * @strr: array of strings
 * Return: 0 on failure
 */
size_t setenviron(char **strr)
{
	int i = 0;
	char *name;
	char *value;

	for (; strr[i]; i++)
		;
	if (i == 3)
	{
		name = strr[1];
		value = strr[2];
	}
	return (0);
}
