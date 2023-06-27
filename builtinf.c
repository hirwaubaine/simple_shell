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
		exit(_atoi(str[1]));
	}
	return (0);
}
