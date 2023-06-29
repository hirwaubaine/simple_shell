#include "shell.h"

char **_copyenviron(void);
void free_environ(void);
char **_getenironv(const char *var);

/**
 * _copyenviron - Creates a copy of the environment
 * Return: If an error occurs - NULL
 */
char **_copyenviron(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * free_environ - Frees the environment copy
 */
void free_environ(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenviron - Gets an environmental variable from the path
 * @var: The name of the environmental variable to get
 * Return: If the environmental variable does not exist - NULL
 */
char **_getenviron(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}
	return (NULL);
}
